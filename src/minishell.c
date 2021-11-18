#include "lexer.h"
#include "parser.h"
#include "minishell.h"
#include "printer.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char *minishell_get_line(void);

int	main(void)
{
	t_list	*l_token;
	t_list	*l_parser;
	char	*input;

	// l_token = NULL;
	// l_parser = NULL;
	// input = ft_strdup("((echo 1) | (echo 2) | (echo 3 | (echo 4))) && echo");
	// l_token = lexer(input);
	// if (l_token != NULL)
	// 	l_parser = parser(l_token);
	// // if (l_token != NULL && l_parser != NULL)
	// // 	execution_wrapper(l_parser);
	// ft_lstclear(&l_parser, c_cmd_destroy);
	// free(input);


	l_token = NULL;
	l_parser = NULL;
	while (1)
	{
		input = minishell_get_line();
		// input = "(( echo 4 ))";
		l_token = lexer(input);
		if (l_token != NULL)
			l_parser = parser(l_token);
		printf("\n\n");
		if (l_token != NULL && l_parser != NULL)
			execution_wrapper(l_parser);
			// execution_recursive(l_parser, (!l_parser->next && cmd_content(l_parser)->type == CMD_PIPELINE));
		// wait(NULL);
		// printf("WAITING END...\n");
		ft_lstclear(&l_parser, c_cmd_destroy);
	}
	return (0);
}

char *minishell_get_line(void)
{
	char	*input;

	input = readline(PROMPT);
	if (input && input[0] != '\0')
		add_history(input);
	rl_on_new_line();
	return (input);
}
