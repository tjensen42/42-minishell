#include "builtin.h"

int	builtin_count_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
		i++;
	return (i);
}
