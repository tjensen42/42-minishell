#include "builtin.h"

int builtin_echo(char **argv)
{
	int		i;
	bool	newline;

	if (!argv || !argv[0])
		return (print_error("minishell: echo: input error"));
	newline = false;
	i = 1;
	while (argv[i] && !ft_strncmp(argv[i], "-n", 3))
		i++;
	if (i == 1)
		newline = true;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	return (0);
}
