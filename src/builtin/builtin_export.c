/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:13:40 by hepple            #+#    #+#             */
/*   Updated: 2022/01/17 15:22:09 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"

static void	print_vars(void);
static bool	is_valid_argument(char *arg);

int	builtin_export(int argc, char **argv)
{
	int	status;
	int	i;

	status = EXIT_SUCCESS;
	if (argc == 1)
		print_vars();
	i = 1;
	while (argc > 1 && argv[i])
	{
		if (is_valid_argument(argv[i]) == false)
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

static void	print_vars(void)
{
	char	**env_copy;
	int		l_var_name;
	int		i;

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
	split_sort(env_copy);
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

static bool	is_valid_argument(char *arg)
{
	int	i;

	if (arg[0] == '\0' || arg[0] == '=')
		return (false);
	i = 0;
	while (arg[i] != '\0' && arg[i] != '=' && env_is_var_char(arg[i]))
		i++;
	if (arg[i] == '\0' || arg[i] == '=')
		return (true);
	else
		return (false);
}
