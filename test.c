#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

// void signal_handler(int sig)
// {
// 	fprintf(stderr, "%d\n", sig);
// }

int main()
{
	// for(int i=0; i < NSIG; i++)
	// 	signal(i, signal_handler);
	char buf[2];

	int i = 0;
	while (1)
	{
		buf[i] = 0;
		i++;
	}

}


