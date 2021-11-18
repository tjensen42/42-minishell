#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// void function(int i)
// {
// 	if (i < 2)
// 		function(i + 1);
// 	else
// 	{
// 		printf("pid: %d\n", getpid());
// 		if (fork() == 0)
// 		{
// 			printf("CHILD: %d\n", getpid());
// 			function(10);
// 			exit(0);
// 		}
// 	}
// }

int	main(void)
{
	// GROUP echo1
	if (fork() == 0)
	{
		printf("PIPELINE echo1\n");
		wait(NULL);
		exit(0);
	}
	// GROUP
	if (fork() == 0)
	{
		printf("PIPELINE GROUP(echo2)\n");
		// Group echo 2
		if (fork() == 0)
		{
			printf("PIPELINE echo2\n");
			wait(NULL);
			exit(0);
		}
		wait(NULL);
		exit(0);
	}
	wait(NULL);
	exit(0);
}
