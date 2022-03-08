#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


int main(int argc, char *argv[])
{
	int *N;
	key_t key;
	int shmid;
	char *pathname = "file.txt";

	if((key = ftok(pathname, 0)) < 0)
	{
		printf("Can\'t generate key\n");
		exit(-1);
	}

	if((shmid = shmget(key, sizeof(int), 0666 | IPC_CREAT | IPC_EXCL)) < 0)
	{

      	if(errno != EEXIST)
      	{
        	 printf("Can\'t create shared memory\n");
        	 exit(-1);
    	}
    	else 
    	{
    	     if((shmid = shmget(key, sizeof(int), 0)) < 0)
    	     {
   	         	printf("Can\'t find shared memory\n");
  	         	exit(-1);
			 }
			 //printf("%d\n", shmid);
        }
    }

	   if((N = (int *)shmat(shmid, NULL, 0)) == (int *)(-1))
	   {
		  printf("Can't attach shared memory\n");
		  exit(-1);
	   }
		
	   *N = argv[0][0];
	   
		//printf("%d\n", *N);
	   
	   printf("Мама: Я вам покушать принесла!\n");
		/*
	   if(shmdt(N) < 0)
	   {
		  printf("Can't detach shared memory\n");
		  exit(-1);
	   }
		*/
		return 0;
}
