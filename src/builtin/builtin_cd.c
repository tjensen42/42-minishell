#include "builtin.h"

int	builtin_cd(int argc UNUSED, char **argv)
{
	char	*dir_name;

	if (argv[1])
		dir_name = argv[1];
	else
	{
		dir_name = getenv("HOME"); /// not our env
		if (dir_name == NULL)
			return (print_error(SHELL_NAME, "cd", NULL, "HOME not set"));
	}
	if (chdir(dir_name) == -1)
	{
		print_error(SHELL_NAME, "cd", dir_name, strerror(errno));
		return (ERROR);
	}
	// update_old_pwd();
	// update_pwd();
	return (0);
}
