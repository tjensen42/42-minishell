#include "builtin.h"

int	bt_cd(char **argv)
{
	char	*dir_name;

	if (argv[1])
		dir_name = argv[1];
	else
	{
		dir_name = getenv("HOME");
		if (dir_name == NULL)
			return (print_error("minishell: cd: HOME not set"));
	}
	if (chdir(dir_name) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(dir_name);
		return (ERROR);
	}
	// update_old_pwd();
	return (0);
}
