/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:14:12 by hepple            #+#    #+#             */
/*   Updated: 2022/01/17 15:22:28 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static const struct s_builtins	g_builtins[] = {
	{"echo", builtin_echo},
	{"cd", builtin_cd},
	{"pwd", builtin_pwd},
	{"env", builtin_env},
	{"export", builtin_export},
	{"unset", builtin_unset},
	{NULL, NULL},
};

int	builtin_check(char **argv)
{
	int	c_name;
	int	i;

	i = 0;
	if (argv[0] && !ft_strncmp(argv[0], "exit", 5))
		return (INT_MAX);
	while (g_builtins[i].name != NULL && argv)
	{
		c_name = ft_strlen(g_builtins[i].name);
		if (argv[0] && !ft_strncmp(argv[0], g_builtins[i].name, c_name + 1))
			return (i + 1);
		i++;
	}
	return (0);
}

int	builtin_exec(char **argv, bool subshell, t_list *l_free)
{
	int	i_builtin;

	i_builtin = builtin_check(argv);
	if (i_builtin == 0)
		return (ERROR);
	errno = 0;
	if (i_builtin == INT_MAX)
		return (builtin_exit(split_count(argv), argv, subshell, l_free));
	return (g_builtins[i_builtin - 1].func(split_count(argv), argv));
}
