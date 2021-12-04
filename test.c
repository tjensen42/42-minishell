#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

int	main(void)
{
	if (putenv("hello=") < 0)
		perror("");
}
