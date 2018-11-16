// Use this to see if a number has an integer square root
#define EPS 1.E-7


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>

double g_time[2];

pthread_mutex_t mutex;
sem_t emptySpaces;
sem_t occupiedSpaces;

int * buffer;
int producer_index;
int consumer_index;

void init(int maxmsg){
	//allocate buffer
	buffer = malloc(maxmsg*sizeof(int));

	//initialize semaphores
	sem_init(&emptySpaces, 0, maxmsg);
	sem_init(&occupiedSpaces, 0, 0);

	//initialize mutex
	pthread_mutex_init(&mutex, NULL);

	producer_index = 0;
	consumer_index = 0;
}

void cleanup()
{
	//delete everything and free memory
	sem_destroy(&emptySpaces);
	sem_destroy(&occupiedSpaces);
	pthread_mutex_destroy(&mutex);
	free(buffer);
}

//id, total_producers, total_num
void* producer(void* input)
{
	int id = ((int *)input)[0];
	int total_producers = ((int *)input)[1];
	int total_num = ((int *)input)[2];
	int buffer_size = ((int *)input)[3];

	int msg = 0;

	//first number produced is the id
	int produced_number = id;

	while(produced_number < total_num)
	{
		sem_wait(&emptySpaces);
		pthread_mutex_lock(&mutex);

		//printf("\nid %d produced %d", id, produced_number);

		//send to buffer
		buffer[producer_index % buffer_size] = produced_number;
		producer_index++;

		//produce	
		//next number that gives remainder == id
		produced_number = produced_number + total_producers;
		
		pthread_mutex_unlock(&mutex);
		sem_post(&occupiedSpaces);
	}

	//printf("\n%d exit", id);
	free(input);
	pthread_exit(0);
}

void* consumer(void* input)
{
	int id = ((int *)input)[0];
	int total_producers = ((int *)input)[1];
	int total_num = ((int *)input)[2];
	int buffer_size = ((int *)input)[3];

	double root;
	int message;

	while(1)
	{
		sem_wait(&occupiedSpaces);
		pthread_mutex_lock(&mutex);
		//consume
		//square root
		message = buffer[consumer_index % buffer_size];
		consumer_index++;

		//once all the numbers have been consumed
		if(consumer_index >= total_num)
		{
			//sem_post(&emptySpaces); only need to free one so the other can go through, in case they are stuck
			//signal to let the other threads go through
			sem_post(&occupiedSpaces);
			pthread_mutex_unlock(&mutex);
			free(input);
			pthread_exit(0);
		}

		root = sqrt(message);
		if(floor(root) == root)
		{
			printf("%d %d %d\n", id, message, (int)root);
		}

		pthread_mutex_unlock(&mutex);
		sem_post(&emptySpaces);
	}
}

int main(int argc, char *argv[])
{
	int num;
	int maxmsg;
	int num_p;
	int num_c;
	int i;
	struct timeval tv;

	if (argc != 5) {
		printf("Usage: %s <N> <B> <P> <C>\n", argv[0]);
		exit(1);
	}

	num = atoi(argv[1]);	/* number of items to produce */
	maxmsg = atoi(argv[2]); /* buffer size                */
	num_p = atoi(argv[3]);  /* number of producers        */
	num_c = atoi(argv[4]);  /* number of consumers        */

	//initialize
	init(maxmsg);
	pthread_t producer_ids[num_p];
	pthread_t consumer_ids[num_c];
	
	gettimeofday(&tv, NULL);
	g_time[0] = (tv.tv_sec) + tv.tv_usec/1000000.;

//create producer threads
	for(i =0; i < num_p; i++)
	{
		int *input = malloc(4*sizeof(int));
		input[0] = i;
		input[1] = num_p;
		input[2] = num;
		input[3] = maxmsg;
		
		if (pthread_create(&producer_ids[i], NULL, producer, input) != 0)
		{
			printf("can't create producer %d", i);
		}
	}
//create consumer threads
	for(int i=0; i < num_c; i++)
	{
		int *input = malloc(4*sizeof(int));
		input[0] = i;
		input[1] = num_p;
		input[2] = num;
		input[3] = maxmsg;

		if (pthread_create(&consumer_ids[i], NULL, consumer, input) != 0)
		{
			printf("can't create consumer %d", i);
		}
	}
	
	//join producers
	for(int j = 0; j < num_p; j++) {
		pthread_join(producer_ids[j], NULL);
	}
	// join consumers
	for(int i = 0; i < num_c; i++) {
		pthread_join(consumer_ids[i], NULL);
	}
	cleanup();

    gettimeofday(&tv, NULL);
    g_time[1] = (tv.tv_sec) + tv.tv_usec/1000000.;

    printf("System execution time: %.6lf seconds\n", \
            g_time[1] - g_time[0]);
	exit(0);
}

