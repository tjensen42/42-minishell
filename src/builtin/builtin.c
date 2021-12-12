#include "builtin.h"

static const struct	s_builtins g_builtins[] = {
	{"echo", builtin_echo},
	{"cd", builtin_cd},
	{"pwd", builtin_pwd},
	{"exit", builtin_exit},
	{"env", builtin_env},
	{"export", builtin_export},
	{"unset", builtin_unset},
	{NULL, NULL},
};

int	builtin_check(char **argv)
{
	int	i;
	int	c_name;

	i = 0;
	while (g_builtins[i].name != NULL)
	{
		c_name = ft_strlen(g_builtins[i].name);
		if (ft_strncmp(argv[0], g_builtins[i].name, c_name + 1) == 0)
			return (i + 1);
		i++;
	}
	return (0);
}

int	builtin_exec(char **argv)
{
	int	i_builtin;

	i_builtin = builtin_check(argv) - 1;
	if (i_builtin == -1)
		return (ERROR);
	errno = 0;
	return (g_builtins[i_builtin].func(split_count(argv), argv));
}
