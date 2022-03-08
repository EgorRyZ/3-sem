#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	
	printf("1-ый процесс\n");
	pid_t pid = fork();
	
	for(int i = 2; i < 11; i++)
		if(pid == 0)
		{
			printf("%d-й процесс\n", i);
			pid = fork();
		}
	
	if(pid)
		printf("%d\n", pid);
	//waitpid(pid);

	return 0;

}
