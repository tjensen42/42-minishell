#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

// extern char **environ;

int	main(void)
{
	char buf[200];

	int bytes = read(STDIN_FILENO, buf, 1);
	buf[bytes] = '\0';
	printf("|%s|", buf);
}
