#include "minishell.h"
#include "parser.h"

int	print_error(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	return (ERROR);
}
