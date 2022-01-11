#include <limits.h>
#include "builtin.h"

int	builtin_pwd(int argc __attribute((unused)),
	char **argv __attribute((unused)))
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
