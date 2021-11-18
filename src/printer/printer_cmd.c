#include <stdio.h>
#include "printer.h"
#include "parser.h"
#include "cmd.h"

static void	printer_cmd_recursive(t_list *l_cmd, bool pipeline);
static bool	printer_pipeline_check(t_list *l_cmd);

void	printer_cmd(t_list *l_cmd)
{
	printf("\e[37;7mCMD:\t\t\e[m");
	printer_cmd_recursive(l_cmd, (!l_cmd->next && cmd_content(l_cmd)->type == CMD_PIPELINE));
	printf("\n");
}

void	printer_cmd_structure(t_list *l_cmd)
{
	t_c_cmd	*c_pg;

	printf("\e[37;7mCMD_STRUCT:\t\e[m");
	while (l_cmd)
	{
		c_pg = cmd_content(l_cmd);
		if (c_pg->type == CMD_PIPELINE)
			printf("PL ");
		else if (c_pg->type == CMD_GROUP)
			printf("GR ");
		else
			printer_other(c_pg->type);
		l_cmd = l_cmd->next;
	}
	printf("\n");
}

static void	printer_cmd_recursive(t_list *l_cmd, bool pipeline)
{
	if (cmd_list_type(l_cmd) == CMD_L_SCMD)
	{
		printer_scmd_pipeline(l_cmd, false);
		return ;
	}
	if (cmd_content(l_cmd)->type == CMD_PIPELINE)
		printer_cmd_recursive(cmd_content(l_cmd)->l_element, true);
	else if (cmd_content(l_cmd)->type == CMD_GROUP)
	{
		printer_other(CMD_O_BRACKET);
		printer_cmd_recursive(cmd_content(l_cmd)->l_element, false);
		printer_other(CMD_C_BRACKET);
	}
	else
		printer_other(cmd_content(l_cmd)->type);
	if (l_cmd->next)
	{
		if (pipeline && printer_pipeline_check(l_cmd))
			printer_other(CMD_PIPE);
		printer_cmd_recursive(l_cmd->next, pipeline);
	}
}

static bool	printer_pipeline_check(t_list *l_cmd)
{
	if (cmd_content(l_cmd)->type & (CMD_C_BRACKET | CMD_GROUP | CMD_PIPELINE))
	{
		if (l_cmd->next && (cmd_content(l_cmd->next)->type
				& (CMD_O_BRACKET | CMD_GROUP | CMD_PIPELINE)))
		{
			return (true);
		}
	}
	return (false);
}
