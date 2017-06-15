#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void *num_words (void *arg) {
    long num_words=0;
    
    //printf("In the first thread function!\n"); 	//USED FOR DEBUGGING
	
    // Cast the argument as an char pointer
    char *n = (char *)arg;
    //printf("Filename was %s\n", n);			//USED FOR DEBUGGING

    FILE * fp;
    fp = fopen(arg,"r");
    int ch;

    while(1)
    {
	ch = fgetc(fp);
	if( feof(fp) )
	{ 
	    break ;
	} else if (ch==' ' || ch=='\n') {
	    num_words++;
	}
	//printf("%c", ch); //USED FOR DEBUGGING
    }
    fclose(fp);
    printf("%d %s\n", num_words,n );
    return (void *) num_words;
}

void main (int arg, char *argv[]) {
    int i,j,rtn[arg-1],t_succ[arg-1];
    int total_num_words = 0;
    //error check for no files provided
    if (arg < 2) {
	printf("No files provided - please provide at least one file to read\n");
	exit(1);
    } else {
	//loop through num args for files
	//printf("file name is: %s",argv[1]);	//USED FOR DEUBGGING
	pthread_t th_id[arg-1];
        for(i=0 ; i<arg-1; i++) {
	    t_succ[i] = pthread_create(&(th_id[i]), NULL, &num_words, (void *)argv[i+1]);
	    if (t_succ[i] == 0){
		//printf("\n Thread created successfully\n");				//USED FOR DEBUGGING
	    } else {
		printf("\ncan't create thread :[%s]", t_succ[i]);
		exit(1);
	    }
	}
	//for loop to joing the threads
	for(j=0; j<arg-1; j++) {
	    if(t_succ[j] == 0) {
		//join threads
		pthread_join(th_id[j], (void *)&rtn[j]);
		total_num_words += rtn[j];
		//printf("Successfully joined thread with value %d\n", rtn[j]);		//USED FOR DEBUGGING
	    }
	}
	printf("%d total\n", total_num_words);
    }
}
