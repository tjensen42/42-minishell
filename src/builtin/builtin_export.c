#include "builtin.h"

static void	export_print_vars(void);

int	builtin_export(int argc, char **argv)
{
	int	i;

	if (argc == 1)
		export_print_vars();
	else if (argc > 1)
	{
		i = 1;
		while (argv[i])
		{
			env_put_var(argv[i]);
			i++;
		}
	}
	return (0);
}

static void	export_print_vars(void)
{
	int	i;
	int	l_var_name;

	i = 0;
	while (g_env[i])
	{
		printf("declare -x ");
		if (ft_strchr(g_env[i], '='))
		{
			l_var_name = ft_strchr(g_env[i], '=') - g_env[i];
			printf("%.*s\n", l_var_name, g_env[i]);
			printf("\"%s\"\n", env_get_value(g_env[i]));
		}
		else
			printf("%s\n", g_env[i]);
		i++;
	}
}
