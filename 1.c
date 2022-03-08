#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{


	int n = 65;
	const char *arg0 = (char *)(&n);
	//const char *arg0 = {"666"};
	
	execl("mama.out", arg0, NULL);
    //(void) execl("b.out",  arg0);

    //printf("Error on program start\n");
    //exit(-1);
	
    return 0;
}

