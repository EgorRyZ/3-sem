#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LAST_MESSAGE 'q'

int main(int argc, char *argv[])
{
	int msqid;

	char pathname[] = "file.txt";

	key_t key;

	struct mymsgbuf
	{
		long mtype;
	} mybuf;

	if((key = ftok(pathname,0)) < 0)
	{
		printf("Can\'t generate key\n");
		exit(-1);
	}


		if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)
		{
			printf("Can\'t get msqid\n");
			exit(-1);
		}

		mybuf.mtype = 1;

		if (msgsnd(msqid, (struct msgbuf *)(&mybuf), 0, 0) < 0)
		{
			printf("Can\'t send message to queue\n");
			msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
			exit(-1);
		}
		
		//for(int j = 0; j < argc; j++)
			//printf("%s\n", argv[j]);
			
		
	if((argc > 1 ? argv[argc - 1][0] : 0) == LAST_MESSAGE)
	{
		mybuf.mtype = LAST_MESSAGE;
		
		if (msgsnd(msqid, (struct msgbuf *)(&mybuf), 0, 0) < 0)
		{
			printf("Can\'t send message to queue\n");
			msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
			exit(-1);
		}
	}
	
	
	printf("Птенец съел порцию\n");
		
		
	return 0;
} 
