#include "parser.h"
#include "minishell.h"

static void	parser_printer_s1_scmd(t_c_scmd *scmd);
static void	parser_printer_s1_other(t_list *l_scmd);

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

void	parser_printer_s1(t_list *l_scmd)
{
	while (l_scmd)
	{
		if (scmd_content(l_scmd)->type == PAR_SCMD)
		{
			parser_printer_s1_scmd(scmd_content(l_scmd));
		}
		else
		{
			parser_printer_s1_other(l_scmd);
		}
		l_scmd = l_scmd->next;
	}
	printf("\n");
}

static void	parser_printer_s1_scmd(t_c_scmd *scmd)
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

static void	parser_printer_s1_other(t_list *l_scmd)
{
	int	type;

	type = scmd_content(l_scmd)->type;
	if (type == PAR_AND)
		printf("\033[0;31m&& \033[m");
	else if (type == PAR_OR)
		printf("\033[0;31m|| \033[m");
	else if (type == PAR_PIPE)
		printf("\033[0;31m| \033[m");
	else if (type == PAR_O_BRACKET)
		printf("\033[0;31m( \033[m");
	else if (type == PAR_C_BRACKET)
		printf("\033[0;31m) \033[m");
	else
		printf("DEAD ");
}
