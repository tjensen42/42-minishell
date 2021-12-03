#include "builtin.h"

static bool	num_is_numeric(char *str);

int	builtin_exit(int argc, char **argv)
{
	int	exit_num;

	ft_putstr_fd("exit\n", 2);
	exit_num = 0; // set to last exit code
	if (argc >= 2 && num_is_numeric(argv[1]) == false)
		return (ERROR);
	else if (argc == 2)
		exit_num = ft_atoi(argv[1]);
	else if (argc > 2)
	{
		print_error(SHELL_NAME, "exit", "too many arguments", NULL);
		exit_num = 255;
	}
	// clear everything
	exit(exit_num);
	return (0);
}

static bool	num_is_numeric(char *str)
{
	int	i;

	i = 0;
	if ((str[0] == '-' || str[0] == '+') && str[1] != '\0')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (false);
		}
		i++;
	}
	return (true);
}
