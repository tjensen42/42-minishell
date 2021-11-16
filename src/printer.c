#include "parser.h"
#include "minishell.h"

static void	parser_printer_l_pg_recursive(t_list *l_pg, bool pipeline);
static void	parser_printer_l_scmd_commands(t_c_scmd *scmd);
static void	parser_printer_other(int type);
void	parser_printer_l_scmd_pipeline(t_list *l_scmd_pipeline, bool newline);

void	lexer_printer(t_list *l_token)
{
	printf("\e[0;35mLEXICAL_ANALYSE:\t\e[m");
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

void	parser_printer_l_scmd_structure(t_list *l_scmd)
{
	printf("\e[0;35mPARSER_L_SCMD_STRUC:\t\e[m");
	while (l_scmd)
	{
		if (scmd_content(l_scmd)->type == PAR_SCMD)
			printf("SCMD ");
		else
			parser_printer_other(scmd_content(l_scmd)->type);
		l_scmd = l_scmd->next;
	}
	printf("\n");
}

void	parser_printer_l_scmd(t_list *l_scmd, bool newline)
{
	printf("\e[0;35mPARSER_L_SCMD:\t\t\e[m");
	while (l_scmd)
	{
		if (scmd_content(l_scmd)->type == PAR_SCMD)
			parser_printer_l_scmd_commands(scmd_content(l_scmd));
		else
			parser_printer_other(scmd_content(l_scmd)->type);
		l_scmd = l_scmd->next;
	}
	if (newline)
		printf("\n");
}

void	parser_printer_l_scmd_pipeline(t_list *l_scmd_pipeline, bool newline)
{
	while (l_scmd_pipeline)
	{
		parser_printer_l_scmd_commands(scmd_content(l_scmd_pipeline));
		if (l_scmd_pipeline->next)
			parser_printer_other(PAR_PIPE);
		l_scmd_pipeline = l_scmd_pipeline->next;
	}
	if (newline)
		printf("\n");
}

void	parser_printer_l_pg(t_list *l_pg)
{
	printf("\e[0;35mPARSER_L_PG:\t\t\e[m");

	parser_printer_l_pg_recursive(l_pg, (pg_content(l_pg)->type == PAR_PIPELINE));
	printf("\n");
}

static void	parser_printer_l_pg_recursive(t_list *l_pg, bool pipeline)
{
	// SCMD PIPELIN
	if (parser_get_list_type(l_pg) == PAR_L_SCMD)
	{
		parser_printer_l_scmd_pipeline(l_pg, false);
		return ;
	}

	// PIPELINE
	if (pg_content(l_pg)->type == PAR_PIPELINE)
	{
		parser_printer_l_pg_recursive(pg_content(l_pg)->l_element, true);
	}

	// GROUP
	else if (pg_content(l_pg)->type == PAR_GROUP)
	{
		parser_printer_other(PAR_O_BRACKET);
		parser_printer_l_pg_recursive(pg_content(l_pg)->l_element, false);
		parser_printer_other(PAR_C_BRACKET);
	}

	// OTHER
	else
	{
		parser_printer_other(pg_content(l_pg)->type);
	}

	// NEXT ITEMS
	if (l_pg->next)
	{
		if (pipeline && (pg_content(l_pg->next)->type == PAR_O_BRACKET || pg_content(l_pg->next)->type == PAR_GROUP || pg_content(l_pg->next)->type == PAR_PIPELINE)
		 	&& (pg_content(l_pg)->type == PAR_C_BRACKET || pg_content(l_pg)->type == PAR_GROUP || pg_content(l_pg)->type == PAR_PIPELINE))
			parser_printer_other(PAR_PIPE);
		parser_printer_l_pg_recursive(l_pg->next, pipeline);
	}
}

// static void	parser_printer_l_pg_recursive(t_list *l_pg)
// {
// 	t_list	*tmp;
// 	t_c_pg	*c_pg;

// 	while (l_pg)
// 	{
// 		c_pg = pg_content(l_pg);
// 		if (c_pg->type == PAR_PIPELINE)
// 		{
// 			tmp = c_pg->l_element;
// 			if (parser_get_list_type(tmp) == PAR_L_SCMD)
// 			{
// 				parser_printer_l_scmd_commands(scmd_content(tmp));
// 			}
// 			else
// 			{
// 				parser_printer_l_pg_recursive(tmp);
// 			}
// 			if (l_pg->next && (pg_content(l_pg->next)->type == PAR_PIPELINE || pg_content(l_pg->next)->type == PAR_GROUP))
// 				parser_printer_other(PAR_PIPE);
// 		}
// 		else if (c_pg->type == PAR_GROUP)
// 		{
// 			parser_printer_other(PAR_O_BRACKET);
// 			parser_printer_l_pg_recursive(c_pg->l_element);
// 			parser_printer_other(PAR_C_BRACKET);
// 		}
// 		else
// 			parser_printer_other(c_pg->type);
// 		l_pg = l_pg->next;
// 	}
// }

void	parser_printer_l_pg_structure(t_list *l_pg)
{
	t_c_pg	*c_pg;

	printf("\e[0;35mPARSER_L_PG_STRUC:\t\e[m");
	while (l_pg)
	{
		c_pg = pg_content(l_pg);
		if (c_pg->type == PAR_PIPELINE)
			printf("P ");
		else if (c_pg->type == PAR_GROUP)
			printf("G ");
		else
			parser_printer_other(c_pg->type);
		l_pg = l_pg->next;
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

static void	parser_printer_other(int type)
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
