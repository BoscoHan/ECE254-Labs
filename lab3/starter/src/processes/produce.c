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

void producer(int id) {
	printf("\nid: %d\n", id);	

	//wait
	//produce
	//signal
	//while(1);
}

void consumer(int id) {
	printf("\n consumer id: %d\n", id);
}


int main(int argc, char *argv[])
{
	int num;
	int maxmsg;
	int num_p;
	int num_c;
	int pid;
	struct timeval tv;

	if (argc != 5) {
		printf("Usage: %s <N> <B> <P> <C>\n", argv[0]);
		exit(1);
	}

	num = atoi(argv[1]);	/* number of items to produce */
	maxmsg = atoi(argv[2]); /* buffer size                */
	num_p = atoi(argv[3]);  /* number of producers        */
	num_c = atoi(argv[4]);  /* number of consumers        */


	gettimeofday(&tv, NULL);
	g_time[0] = (tv.tv_sec) + tv.tv_usec/1000000.;

	//code here----------------------------------------------
	
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
				producer(index_p);
				break;
			}

			else if(pid < 0) {
				printf("fork failed");
			}
		}
	}

	//create consumers
	if (num_c) {
		pid = 0;
		int index_c = 0;
		for (index_c = 0; index_c < num_c; index_c++) {
			pid = fork();

			if (pid == 0) {
				consumer(index_c);
				break;
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