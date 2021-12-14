#include "builtin.h"
#include "exec.h"

int builtin_echo(int argc UNUSED, char **argv)
{
	int		i;
	bool	newline;

	newline = false;
	i = 1;
	while (argv[i] && !ft_strncmp(argv[i], "-n", 3))
		i++;
	if (i == 1)
		newline = true;

	///// delete this after variable expansion....
	if (argv[i] && ft_strncmp(argv[i], "$?", 3) == 0)
	{
		ft_putnbr_fd(exit_status_get(), STDOUT_FILENO);
		ft_putchar_fd('\n', 1);
		return (0);
	}
	///// END delete this after variable expansion....

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
