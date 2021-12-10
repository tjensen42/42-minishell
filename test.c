#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

int	main(void)
{
	char buf[200];

	int size = read(123, buf, 20);
	buf[size] = '\0';
	write(1, buf, size);
}
