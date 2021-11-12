#include "parser.h"
#include "minishell.h"

static void	parser_printer_l_scmd_commands(t_c_scmd *scmd);
static void	parser_printer_l_scmd_other(int type);

void	lexer_printer(t_list *l_token)
{
	if (l_token != NULL)
	{
		while (l_token->next != NULL)
		{
			if (token_content(l_token)->flags & TOK_CONNECTED)
				printf("%s \033[0;35m+ \033[m", token_content(l_token)->string);
			else
				printf("%s \033[0;32m: \033[m", token_content(l_token)->string);
			l_token = l_token->next;
		}
		printf("%s\n", token_content(l_token)->string);
	}
}

void	parser_printer_l_scmd(t_list *l_scmd)
{
	while (l_scmd)
	{
		if (scmd_content(l_scmd)->type == PAR_SCMD)
		{
			parser_printer_l_scmd_commands(scmd_content(l_scmd));
		}
		else
		{
			parser_printer_l_scmd_other(scmd_content(l_scmd)->type);
		}
		l_scmd = l_scmd->next;
	}
	printf("\n");
}

void	parser_printer_l_group_structure(t_list *l_pg)
{
	t_c_pg	*c_pg;

	while (l_pg)
	{
		c_pg = pg_content(l_pg);
		if (c_pg->type == PAR_PIPELINE)
			printf("P ");
		else if (c_pg->type == PAR_GROUP)
		{
			printf("G ");
			//parser_printer_l_pipeline(pg_content(l_pg)->l_element);
		}
		else 	
		{
			parser_printer_l_scmd_other(c_pg->type);
		}
		l_pg = l_pg->next;
	}
	printf("\n");
}

void	parser_printer_l_pipeline_structure(t_list *l_pipeline)
{
	t_c_pg	*c_pipeline;

	while (l_pipeline)
	{
		c_pipeline = pg_content(l_pipeline);
		if (c_pipeline->type == PAR_PIPELINE)
		{
			printf("P ");
		}
		else 	
		{
			parser_printer_l_scmd_other(c_pipeline->type);
		}
		l_pipeline = l_pipeline->next;
	}
	printf("\n");
}

void	parser_printer_l_pipeline(t_list *l_pipeline)
{
	t_c_pg	*c_pipeline;
	t_list	*tmp;

	while (l_pipeline)
	{
		c_pipeline = pg_content(l_pipeline);
		if (c_pipeline->type == PAR_PIPELINE)
		{
			tmp = c_pipeline->l_element;
			while (tmp)
			{
				parser_printer_l_scmd_commands(scmd_content(tmp));
				tmp = tmp->next;
				if (tmp)
					parser_printer_l_scmd_other(PAR_PIPE);		
			}
		}
		else 	
		{
			parser_printer_l_scmd_other(c_pipeline->type);
		}
		l_pipeline = l_pipeline->next;
	}
	printf("\n");
}

static void	parser_printer_l_scmd_commands(t_c_scmd *scmd)
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

static void	parser_printer_l_scmd_other(int	type)
{
	if (type == PAR_AND)
		printf("\033[0;31m&& \033[m");
	else if (type == PAR_OR)
		printf("\033[0;31m|| \033[m");
	else if (type == PAR_PIPE)
		printf("\033[0;31m| \033[m");
	else if (type == PAR_O_BRACKET)
		printf("\033[0;36m( \033[m");
	else if (type == PAR_C_BRACKET)
		printf("\033[0;36m) \033[m");
	else
		printf("DEAD ");
}
