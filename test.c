#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int	main(void)
{
	int i;
	char buf[256];

	i = read(0, &buf, 21);
	buf[i] = '\0';
	printf("%s", buf);
}
