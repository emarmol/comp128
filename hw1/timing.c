#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/times.h>

//read program  file from command line
void main (int arg, char *argv[]) {	
    
    static clock_t st_time;
    static clock_t en_time;
    static struct tms st_cpu;
    static struct tms en_cpu;
    static clock_t walltime;
    long i, j;
    int status;
    st_time =  times(&st_cpu);
	
    if (arg < 2) { //error handling for no. arguments
	printf("Invalid number of arguments provided - 2 are required\n");
    } else {
	pid_t parent_wait, pid;

	for(i=0; i < 1000; i++) {
	        pid = fork(); //fork & call timing analysis

		if (pid < 0 ) {
	    		printf("Error occurred while trying to fork\n"); //error occurred
		} else if (pid == 0) {
	    		printf("Child process - going to execute program\n"); //child process executing program
	    		execv(argv[1], NULL);
		} else {
	    		parent_wait = wait(&status);
			printf("parent process - waiting for child to finish\n"); //parent process waiting for child

			if (parent_wait == -1) {
				printf("Error occurred\n");	
	    		}
	       	        if (status == 0 ) {
				printf("Child process terminated normally\n"); //finished child process
	    		} else if (status == 1) {
				printf("Error occurred with child process termination\n"); //error occurred in child process termination
	    		} else {
				printf("None of above are true\n");
	    		}
		}
	}

	en_time = times(&en_cpu);

	printf("FINAL Timing analysis:   utime  %jd       stime  %jd      cutime  %jd      cstime  %jd        wallclock %jd\n",
	       (en_cpu.tms_utime - st_cpu.tms_utime),
	       (en_cpu.tms_stime - st_cpu.tms_stime),
	       (en_cpu.tms_cutime - st_cpu.tms_cutime),
	       (en_cpu.tms_cstime - st_cpu.tms_cstime),
	       (en_time - st_time));
    }
}
