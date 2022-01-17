/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:51:43 by hepple            #+#    #+#             */
/*   Updated: 2022/01/17 15:52:21 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printer.h"
#include "cmd.h"

static void	printer_cmd_recursive(t_list *l_cmd);
static void	printer_pipeline(t_list *pipeline);
static void	printer_group(t_list *group);

void	printer_cmd(t_list *l_cmd)
{
	printf("\e[37;7mCMD:\t\t\e[m");
	printer_cmd_recursive(l_cmd);
	printf("\n");
}

void	printer_structure(t_list *l_cmd)
{
	printf("\e[37;7mSTRUCT:\t\t\e[m");
	while (l_cmd)
	{
		if (cmd_type(l_cmd) == CMD_SCMD)
			printf("SCMD ");
		else if (cmd_type(l_cmd) == CMD_PIPELINE)
			printf("PL ");
		else if (cmd_type(l_cmd) == CMD_GROUP)
			printf("GR ");
		else
			printer_other(cmd_type(l_cmd));
		l_cmd = l_cmd->next;
	}
	printf("\n");
}

static void	printer_cmd_recursive(t_list *l_cmd)
{
	if (cmd_type(l_cmd) == CMD_SCMD)
		printer_scmd(scmd_content(l_cmd));
	else if (cmd_type(l_cmd) == CMD_PIPELINE)
		printer_pipeline(l_cmd);
	else if (cmd_type(l_cmd) == CMD_GROUP)
		printer_group(l_cmd);
	else
		printer_other(cmd_type(l_cmd));
	if (l_cmd->next)
		printer_cmd_recursive(l_cmd->next);
}

static void	printer_pipeline(t_list *pipeline)
{
	t_list	*iter;

	iter = cmd_content(pipeline)->l_element;
	while (iter)
	{
		if (cmd_type(iter) == CMD_SCMD)
			printer_scmd(scmd_content(iter));
		else if (cmd_type(iter) == CMD_GROUP)
			printer_group(iter);
		if (iter->next)
			printer_other(CMD_PIPE);
		iter = iter->next;
	}
}

static void	printer_group(t_list *group)
{
	printer_other(CMD_O_BRACKET);
	printer_cmd_recursive(cmd_content(group)->l_element);
	printer_other(CMD_C_BRACKET);
}
