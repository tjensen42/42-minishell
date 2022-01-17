#include "builtin.h"
#include "env.h"

static void	export_print_vars(void);
static bool	export_is_valid_argument(char *arg);
static void	export_sort_split(char **split);

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
	int		i;
	int		l_var_name;
	char	**env_copy;

	if (g_env == NULL || *g_env == NULL)
		return ;
	env_copy = malloc((split_count(g_env) + 1) * sizeof(char *));
	if (env_copy == NULL)
	{
		print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM));
		return ;
	}
	env_copy = ft_memcpy(env_copy, g_env,
			(split_count(g_env) + 1) * sizeof(char *));
	export_sort_split(env_copy);
	i = 0;
	while (env_copy[i])
	{
		l_var_name = ft_strchr(env_copy[i], '=') - env_copy[i];
		printf("%.*s", l_var_name + 1, env_copy[i]);
		printf("\"%s\"\n", env_get_value(env_copy[i]));
		i++;
	}
	free(env_copy);
}

static bool	export_is_valid_argument(char *arg)
{
	int	i;

	if (arg[0] == '\0' || arg[0] == '=')
		return (false);
	i = 0;
	while (arg[i] != '\0' && arg[i] != '=' && is_var_char(arg[i]))
		i++;
	if (arg[i] == '\0' || arg[i] == '=')
		return (true);
	else
		return (false);
}

static void	export_sort_split(char **split)
{
	int		i;
	int		j;
	int		i_strs;
	char	*tmp;

	i_strs = split_count(split);
	i = 0;
	while (i < i_strs - 1)
	{
		j = 0;
		while (j < (i_strs - 1 - i))
		{
			if (ft_strncmp(split[j], split[j + 1], ft_strlen(split[j]) + 1) > 0)
			{
				tmp = split[j];
				split[j] = split[j + 1];
				split[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}
