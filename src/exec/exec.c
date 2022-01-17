/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:36:04 by hepple            #+#    #+#             */
/*   Updated: 2022/01/17 16:08:09 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>

#include "exec.h"
#include "cmd.h"

static bool	exec_operator_skip(t_list *l_cmd);

int	exec_recursive(t_list *l_cmd, bool subshell, t_list *l_free)
{
	if (cmd_type(l_cmd) == CMD_SCMD)
		exec_exit_status_set(exec_scmd(l_cmd, subshell, l_free));
	else if (cmd_type(l_cmd) == CMD_PIPELINE)
		exec_exit_status_set(exec_pipeline(l_cmd, l_free));
	else if (cmd_type(l_cmd) == CMD_GROUP)
		exec_exit_status_set(exec_group(l_cmd, l_free));
	if (l_cmd->next)
	{
		l_cmd = l_cmd->next;
		while (l_cmd && exec_operator_skip(l_cmd))
			l_cmd = l_cmd->next->next;
		if (l_cmd != NULL)
			exec_exit_status_set(exec_recursive(l_cmd->next, subshell, l_free));
	}
	return (exec_exit_status_get());
}

void	exec_free_all(char **argv, t_list *l_free)
{
	if (argv)
		ft_free_split(&argv);
	if (l_free)
		ft_lstclear(&l_free, c_cmd_destroy);
	if (g_env)
		ft_free_split(&g_env);
	rl_clear_history();
}

static bool	exec_operator_skip(t_list *l_cmd)
{
	if (cmd_content(l_cmd)->type & CMD_AND && exec_exit_status_get() != 0)
		return (true);
	else if (cmd_content(l_cmd)->type & CMD_OR && exec_exit_status_get() == 0)
		return (true);
	else
		return (false);
}
