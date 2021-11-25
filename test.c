#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int	main(void)
{
	// printf("%s\n", *environ);
	if (environ)
		for (char **ep = environ; *ep; ep++)
			(void)printf("%s\n", *ep);
	// printf("%s\n", getenv("testprogramm"));
}
