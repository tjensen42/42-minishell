#include "parser.h"
#include "minishell.h"

void	lexer_printer(t_list *l_token)
{
	if (l_token != NULL)
	{
		while (l_token->next != NULL)
		{
			printf("%s : ", token_content(l_token)->string);
			l_token = l_token->next;
		}
		printf("%s\n", token_content(l_token)->string);
	}
}

void	parser_printer(t_list *l_command)
{
	int i;
	int type;

	while (l_command)
	{
		if (element_content(l_command)->type == PAR_CMD)
		{
			//printf("cmd:\t");
			i = 0;
			while (element_content(l_command)->cmd[i])
			{
				if (i == 0)
					printf("\033[0;33m%s \033[m", element_content(l_command)->cmd[i]);
				else
					printf("\033[0;32m%s \033[m", element_content(l_command)->cmd[i]);
				i++;
			}
			i = 0;
			while (element_content(l_command)->redirs[i])
			{
				printf("\033[0;36m%s \033[m", element_content(l_command)->redirs[i]);
				printf("\033[0;34m%s \033[m", element_content(l_command)->files[i]);
				i++;
			}
		}
		else
		{
			type = element_content(l_command)->type;
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
		l_command = l_command->next;
	}
	printf("\n");
}