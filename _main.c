#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define LAST_MESSAGE 'q'


int main()
{
	int n;
	int *N;
	int count;
	printf("Введите, чему равно N:\n");
	scanf("%d", &n);
	key_t key;
	int shmid;
	char *pathname = "file.txt";
	
	if((key = ftok(pathname, 0)) < 0)
	{
		printf("Can\'t generate key\n");
		exit(-1);
	}

	if((shmid = shmget(key, sizeof(N), 0666 | IPC_CREAT | IPC_EXCL)) < 0)
	{

      	if(errno != EEXIST)
      	{
        	 printf("Can\'t create shared memory\n");
        	 exit(-1);
    	}
    	else 
    	{
    	     if((shmid = shmget(key, sizeof(N), 0)) < 0)
    	     {
   	         	printf("Can\'t find shared memory\n");
  	         	exit(-1);
			 }
        }
    }
    
    
    	if((N = (int *)shmat(shmid, NULL, 0)) == (int *)(-1))
	   	{
		  printf("Can't attach shared memory\n");
		  exit(-1);
	   	}


	   
	*N = n;
	
	
	int msqid;

	struct mymsgbuf
	{
		long mtype;
	} mybuf;


	if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)
	{
		printf("Can\'t get msqid\n");
		exit(-1);
	}

	while(1)
	{

		

		if(msgrcv(msqid, (struct msgbuf *) &mybuf, 0, 0, 0) < 0)
		{
			printf("Can\'t receive message from queue\n");
			exit(-1);
		}
		
		count = --(*N);
		printf("Осталось %d порций в миске\n", count);
		
		if(!count)
		{
			const char* arg0 = (char *)(&n);
			pid_t x = fork();
			if(x == 0)
				execl("mama.out", arg0, NULL);
		}
	
		
		if (mybuf.mtype == LAST_MESSAGE)
		{
			
			msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
			
		   if(shmdt(N) < 0)
		   {
			  printf("Can't detach shared memory\n");
			  exit(-1);
		   }

			exit(0);
		}


	}



	   return 0;
} 
