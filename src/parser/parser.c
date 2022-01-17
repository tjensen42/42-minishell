/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:46:05 by hepple            #+#    #+#             */
/*   Updated: 2022/01/17 15:46:09 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "env.h"
#include "printer.h"

static int	parser_recursive_merge(t_list **l_cmd);

t_list	*parser(t_list *l_token)
{
	t_list	*l_cmd;

	l_cmd = parser_scmd_tokens(l_token);
	if (l_cmd == NULL)
		return (NULL);
	if (env_var_is_value(DEBUG_ENV, "printer"))
	{
		printer_cmd(l_cmd);
		printer_structure(l_cmd);
	}
	if (parser_recursive_merge(&l_cmd) == ERROR)
	{
		ft_lstclear(&l_cmd, c_cmd_destroy);
		return (NULL);
	}
	if (env_var_is_value(DEBUG_ENV, "printer"))
	{
		printer_cmd(l_cmd);
		write(1, "\n", 1);
	}
	return (l_cmd);
}

static int	parser_recursive_merge(t_list **l_cmd)
{
	int	group;
	int	pipeline;

	group = 1;
	pipeline = 1;
	while (group > 0 || pipeline > 0)
	{
		group = parser_cmd_group_merge(l_cmd);
		if (group == ERROR)
			return (ERROR);
		if (group > 0 && env_var_is_value(DEBUG_ENV, "printer"))
			printer_structure(*l_cmd);
		pipeline = parser_cmd_pipeline_merge(l_cmd);
		if (pipeline == ERROR)
			return (ERROR);
		if (pipeline > 0 && env_var_is_value(DEBUG_ENV, "printer"))
			printer_structure(*l_cmd);
	}
	return (0);
}
