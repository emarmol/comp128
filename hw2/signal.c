/*
This program calls the alarm to go off after x amount of seconds
The while loop check for if the alarm signal has been set - if so,
the alarm handler is called. If there is no error, the message will
print that the signal was caught, and the program exits.
*/


#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void alarm_handler(int);

int main () {
    const int duration = 4;

    int alrm = alarm(duration); // set off alarm after x seconds
    printf("alarm has successfully been called (%d) \nsigalrm set (%d) for %d seconds\n", alrm, SIGALRM, duration);

    while(SIGALRM == 14){
	    signal(SIGALRM, alarm_handler); // to setup handler 
    }
	return 0;
}

void alarm_handler(int sig_alarm) {

      if (sig_alarm != SIGALRM)
    	printf("Error occurred with alarm signal\n");

	printf("Caught signal %d, program will exit...\n", sig_alarm);
   	exit(1);
}
