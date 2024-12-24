#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int fatal(char *s);
int main(void)
{
	pid_t pid;
	int status;
//	int * ret = &status;
	switch(pid = fork()) {
		case -1:
			fatal("fork failed.");
			break;
		case 0:
//			sleep(60);
//			execl("/bin/ls","ls","-l",NULL);
			execl("/bin/ls","ls","-l",NULL);
			fatal("exec failed.");
			break;
		default:
			wait(&status);
			printf("ls completed  %d\n", status >> 8);
			exit(0);
	}
}
int fatal(char *s)
{
	perror(s);
	exit(1);
}
