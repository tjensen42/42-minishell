#include <stdio.h>
#include "printer.h"
#include "cmd.h"

void	printer_scmd(t_c_scmd *scmd)
{
	t_list	*tmp;
	bool	command;

	command = true;
	tmp = scmd->l_argv;
	while (tmp)
	{
		if (command == true)
		{
			printf("\033[0;33m%s \033[m", token_content(tmp)->string);
			command = false;
		}
		else
			printf("\033[0;32m%s \033[m", token_content(tmp)->string);
		tmp = tmp->next;
	}
	tmp = scmd->l_redir;
	while (tmp)
	{
		if (token_content(tmp)->flags & TOK_REDIR)
			printf("\033[0;35m%s \033[m", token_content(tmp)->string);
		else
			printf("\033[0;34m%s \033[m", token_content(tmp)->string);
		tmp = tmp->next;
	}
}

void	printer_other(int type)
{
	if (type == CMD_AND)
		printf("\033[0;31m&& \033[m");
	else if (type == CMD_OR)
		printf("\033[0;31m|| \033[m");
	else if (type == CMD_PIPE)
		printf("\033[0;31m| \033[m");
	else if (type == CMD_O_BRACKET)
		printf("\033[0;36m( \033[m");
	else if (type == CMD_C_BRACKET)
		printf("\033[0;36m) \033[m");
	else
		printf("ERROR ");
}

void	printer_scmd_pipeline(t_list *l_scmd_pipeline, bool newline)
{
	while (l_scmd_pipeline)
	{
		printer_scmd(scmd_content(l_scmd_pipeline));
		if (l_scmd_pipeline->next)
			printer_other(CMD_PIPE);
		l_scmd_pipeline = l_scmd_pipeline->next;
	}
	if (newline)
		printf("\n");
}
