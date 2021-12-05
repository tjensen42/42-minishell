#include "builtin.h"
#include "env.h"

static void	export_print_vars(void);
static bool	export_is_valid_argument(char *arg);

int	builtin_export(int argc, char **argv)
{
	int	i;
	int	status;

	status = EXIT_SUCCESS;
	if (argc == 1)
		export_print_vars();
	i = 1;
	while (argc > 1 && argv[i])
	{
		if (export_is_valid_argument(argv[i]) == false)
		{
			print_error(SHELL_NAME, argv[i], NULL, "not a valid identifier");
			status = EXIT_FAILURE;
		}
		else if (ft_strchr(argv[i], '='))
			env_put_var(argv[i]);
		i++;
	}
	return (status);
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

static bool	export_is_valid_argument(char *arg)
{
	if (!ft_strchr(arg, '=') && ft_strchr(arg, '?'))
		return (false);
	else if (ft_strchr(arg, '=') && ft_strchr(arg, '?'))
	{
		if (ft_strchr(arg, '?') < ft_strchr(arg, '='))
			return (false);
	}
	return (true);
}
