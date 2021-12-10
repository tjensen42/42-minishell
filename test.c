#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

int	main(void)
{
	if (wait(NULL) < 0)
		perror("");
}
