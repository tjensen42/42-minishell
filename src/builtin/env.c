#include "builtin.h"

int	builtin_env(void)
{
	int	i;

	if (g_env == NULL)
		return (print_error(SHELL_NAME, "env", NULL, "env not set"));
	i = 0;
	while (g_env[i])
	{
		ft_putendl_fd(g_env[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
