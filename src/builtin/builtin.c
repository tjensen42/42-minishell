#include "builtin.h"

int	builtin_check(char **argv)
{
	int			i;
	const char	*builtins[] = {
		"echo",
		"cd",
		"pwd",
		"exit",
		"env",
		"export",
		"unset",
		NULL
	};

	i = 0;
	while (builtins[i] != NULL)
	{
		if (ft_strncmp(argv[0], builtins[i], ft_strlen(builtins[i]) + 1) == 0)
			return (i + 1);
		i++;
	}
	return (0);
}

int	builtin_exec(char **argv)
{
	int					i_builtin;
	const t_builtins	builtins_func[] = {
		builtin_echo,
		builtin_cd,
		builtin_pwd,
		builtin_exit,
		builtin_env,
		builtin_export,
		builtin_unset,
		NULL
	};

	i_builtin = builtin_check(argv) - 1;
	if (i_builtin == -1)
		return (ERROR);
	return (builtins_func[i_builtin](split_count(argv), argv));
}
