#include "builtin.h"

int	builtin_env(void)
{
	int	i;

	if (g_env == NULL)
		return (print_error("minishell: env: env not set"));
	i = 0;
	while (g_env[i])
	{
		printf("%s\n", g_env[i]);
		i++;
	}
	return (0);
}
