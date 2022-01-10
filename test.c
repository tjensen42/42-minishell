#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

void sig_ctl(int sig)
{
	kill(getpid(), SIG)
}

int	main(void)
{

	// printf("errno: %d\n", errno);
	// close(0);
	// read(0, buf, 200);
	// printf("errno: %d\n", errno);

	signal(SIGINT, sig_ctl);
	char buf[200];
	int read_rt = read(0, buf, 200);
	printf("read_rt: %d, errno: %d, buf: %s\n", read_rt, errno, buf);
}
