#include <limits.h>
#include "builtin.h"

int	builtin_pwd(int argc UNUSED, char **argv UNUSED)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, sizeof(buf)))
	{
		ft_putendl_fd(buf, STDOUT_FILENO);
		return (0);
	}
	else
	{
		print_error(SHELL_NAME, "pwd", NULL, strerror(errno));
		errno = 0;
		return (EXIT_FAILURE);
	}
}
