#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/times.h>
#include <sys/time.h>

int nothing() {
    return 0;
}

int array() {
    int temp_array[2] = {2,4};

    for(int j = 0 ; j < 1; j++) {
	temp_array[j] = 0;
//	printf("Element[%d] = %d\n", j, temp_array[j] );
    }
    return 0;
}

int ret_mult(int a, int b) {
    return (a * b);
}

void main() {
    static int iterations = 1000000;
    float avgSysProcess, avgFuncProcess1, avgFuncProcess2, avgFuncProcess3;

    struct timeval tv1,tv2;

    time_t start_time;
    time_t end_time;

    //average function call 1
    gettimeofday(&tv1, NULL);
    for(int i=0; i < iterations; i++) {
	    nothing();
    }
    gettimeofday(&tv2, NULL);
    avgFuncProcess1 = ((((tv2.tv_sec*1000000)+(tv2.tv_usec))*1000)- (((tv1.tv_sec*1000000)+(tv1.tv_usec))*1000))/(iterations*1.0); // time in microseconds

    //average function call 2
    int product;
    gettimeofday(&tv1, NULL);
    for(int i=0; i < iterations; i++) {
    	product = ret_mult(1000,14);
    }
    gettimeofday(&tv2, NULL);
    avgFuncProcess2 = ((((tv2.tv_sec*1000000)+(tv2.tv_usec))*1000)- (((tv1.tv_sec*1000000)+(tv1.tv_usec))*1000))/(iterations*1.0); // time in microseconds


    //average function call 3
    gettimeofday(&tv1, NULL);
    for(int i=0; i < iterations; i++) {
        array();
    }
    gettimeofday(&tv2, NULL);
    avgFuncProcess3 = ((((tv2.tv_sec*1000000)+(tv2.tv_usec))*1000)- (((tv1.tv_sec*1000000)+(tv1.tv_usec))*1000))/(iterations*1.0); //time in microseconds
    
    //average system call
    int pid;
    gettimeofday(&tv1, NULL); 
    for(int i=0; i < iterations; i++) {
	    pid = getpid();
    }
    gettimeofday(&tv2, NULL); 

    avgSysProcess = ((((tv2.tv_sec*1000000)+(tv2.tv_usec))*1000)- (((tv1.tv_sec*1000000)+(tv1.tv_usec))*1000))/(iterations*1.0); //time in microseconds

    printf("Output:   average function call 1  %f     average function call 2  %f     average function call 3  %f     average system call pid time %f \n",
           avgFuncProcess1,
           avgFuncProcess2,
	   avgFuncProcess3,
           avgSysProcess);
}
