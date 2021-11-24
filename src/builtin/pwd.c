#include <limits.h>
#include "builtin.h"

int	builtin_pwd(void)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, sizeof(buf)))
	{
		ft_putendl_fd(buf, STDOUT_FILENO);
		return (0);
	}
	else
	{
		perror("minishell: pwd: ");
		return (ERROR);
	}
}
