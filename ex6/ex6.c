/*
Write a program that will find the average time it takes for your computer
to make a system call an empty write to stdout. Your program should use the 
`clock_gettime` procedure to time how long a single system call takes. It'll 
do this for one million iterations, and then find the average of all of those 
iterations in nanoseconds.
For some helpful documentation and examples of using time-related system calls,
visit this site: https://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/gettime.html
While the linked site does say that `clock_gettime()` does not work on OSX, this 
turns out to only be the case for OSX versions < 10.12. Anything later than that 
and `clock_gettime()` should work just fine. 
*/

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>	/* for uint64 definition */


#define number_iter 1000000
#define BILLION 1000000000L

int localpid(void) {
	static int a[9] = { 0 };
	return a[0];
}


int main()
{
    uint64_t diff;
	struct timespec start, end;
	int i;
    double avg;

    double approxRollingAverage (double avg, double new_sample) {

    avg -= avg / 1000000;
    avg += new_sample / 1000000;

    return avg;
    }
    
	/* measure monotonic time */
	clock_gettime(CLOCK_MONOTONIC, &start);	/* mark start time */
	//sleep(1);
    fprintf( stdout, "" );
	clock_gettime(CLOCK_MONOTONIC, &end);	/* mark the end time */

	diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	//printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff);
    //printf("time = %d\n", approxRollingAverage(diff, diff));//create the first average
    approxRollingAverage(diff, diff);//create the first average

    for(i=1; i<1000000; i++){
        /* measure monotonic time */
	clock_gettime(CLOCK_MONOTONIC, &start);	/* mark start time */
    fprintf( stdout, "" );
	clock_gettime(CLOCK_MONOTONIC, &end);	/* mark the end time */
	diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    approxRollingAverage(avg, diff);//update the average 1million times
    }
    printf("This is the avg after 1 million iterations %d\n", avg);
    return 0;
}
