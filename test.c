#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

extern char **environ;

int	main(void)
{
	int pid;
	char *argv[3];

	pid = fork();
	if (pid == 0)
	{
		argv[0] = strdup("/bin/sleep");
		argv[1] = strdup("100");
		argv[2] = NULL;
		execve(argv[0], argv, environ);
		write(2, "ERROR\n", 6);
		exit(sleep(10));
	}
	sleep(15);
	kill(0, SIGINT);
	// wait(NULL);
	// wait(NULL);
}
