#include "builtin.h"
#include "env.h"

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
			if (ft_strchr(argv[i], '='))
				env_put_var(argv[i]);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

static void	export_print_vars(void)
{
	int	i;
	int	l_var_name;

	if (g_env == NULL)
		return ;
	i = 0;
	while (g_env[i])
	{
		l_var_name = ft_strchr(g_env[i], '=') - g_env[i];
		printf("%.*s", l_var_name + 1, g_env[i]);
		printf("\"%s\"\n", env_get_value(g_env[i]));
		i++;
	}
}
