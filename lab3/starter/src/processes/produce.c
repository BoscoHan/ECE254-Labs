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

double g_time[2];
const char * qname = "/buffer";

void producer(int id, int total_producers, int total_num, int queue_size) 
{
	int produced_number;
	//printf("\nid: %d\n", id);
	
	mode_t mode = S_IRUSR | S_IWUSR;
	struct mq_attr attr;
	mqd_t qdes;

	attr.mq_flags = 0;
	attr.mq_msgsize = sizeof(int);
	attr.mq_maxmsg = queue_size;

	//returns message queue descriptor, to send message only
	qdes = mq_open(qname, O_WRONLY, mode, &attr);

	if (qdes == -1 ) 
	{
		printf("mq_open() failed");
		perror("mq_open() failed");
		exit(1);
	}
	//printf("\nid: %d\n", id);
	//produce
	produced_number = id;
	while(produced_number < total_num)
	{
		//last place it gets to before failing
		printf("\nid: %d\n", id);
		//send
		if (mq_send(qdes,(char*)&produced_number, sizeof(int), 0) == -1)
		{
			printf("\nid %d: mq_send failed for number %d", id, produced_number);
			perror("\nmq_send failed");
			exit(1);
		}
		printf("\nid %d produced %d", id, produced_number);
		//next number that gives remainder == id
		produced_number = produced_number + total_producers;
	}

	mq_close(qdes);
	exit(0);
}

void consumer(int id) 
{
	//printf("\n consumer id: %d\n", id);

	//returns message queue descriptor, to write and receive message 
	mqd_t qdes = mq_open(qname, O_RDWR);

}


int main(int argc, char *argv[])
{
	int num;
	int maxmsg;
	int num_p;
	int num_c;
	int pid;
	struct timeval tv;
	//used in queue
	//const char * qname;
	mqd_t qdes;
	struct mq_attr attr;


	if (argc != 5) {
		printf("Usage: %s <N> <B> <P> <C>\n", argv[0]);
		exit(1);
	}

	num = atoi(argv[1]);	/* number of items to produce */
	maxmsg = atoi(argv[2]); /* buffer size                */
	num_p = atoi(argv[3]);  /* number of producers        */
	num_c = atoi(argv[4]);  /* number of consumers        */

	attr.mq_flags = 0;
	attr.mq_maxmsg = maxmsg;
	attr.mq_msgsize = sizeof(int);


	gettimeofday(&tv, NULL);
	g_time[0] = (tv.tv_sec) + tv.tv_usec/1000000.;

	//code here----------------------------------------------
	qdes = mq_open(qname, O_CREAT | O_RDWR, (S_IRUSR | S_IWUSR), &attr);
	if (qdes == -1 ) 
	{
		perror("mq_open() failed");
		exit(1);
	}
	
	//create producers
	if (num_p) {
		//fork returns 0 to newly created child process
		pid = 0;
		int index_p;
		for(index_p = 0; index_p < num_p; index_p++) {
			//parent continues to fork children until i = num_p
			pid = fork();

			if(pid == 0) {
				//child creates producer and breaks out
				producer(index_p, num_p, num, maxmsg);
			}

			else if(pid < 0) {
				printf("fork failed");
			}
		}
	}

	//create consumers
	if (num_c) {
		//fork returns 0 to newly created child process
		pid = 0;
		int index_c = 0;
		for (index_c = 0; index_c < num_c; index_c++) {
			//parent continues to fork children until i = num_p
			pid = fork();

			if (pid == 0) {
				//child creates producer and breaks out
				consumer(index_c);
				exit(0);
			}

			else if (pid < 0) {
				printf("fork failed");
			}
		}
	}

	//--------------------------------------------------------
   
    gettimeofday(&tv, NULL);
    g_time[1] = (tv.tv_sec) + tv.tv_usec/1000000.;

    printf("System execution time: %.6lf seconds\n", \
            g_time[1] - g_time[0]);
	exit(0);
}