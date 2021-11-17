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

	// input = ft_strdup("<in grep 42 | wc -l && (echo 1 2 3 > out 4 || echo 2 >out >>out'out')");
	// l_token = lexer(input);
	// if (l_token != NULL)
	// 	l_parser = parser(l_token);
	// ft_lstclear(&l_parser, c_cmd_destroy);
	// free(input);

	// l_token = NULL;
	// l_parser = NULL;
	// while (1)
	// {
	// 	/* code */
	// }


	while (1)
	{
		input = minishell_get_line();
		l_token = lexer(input);
		if (l_token != NULL)
			l_parser = parser(l_token);
		ft_lstclear(&l_parser, c_cmd_destroy);
		// if (l_token != NULL && l_parser != NULL)
		// 	execute(l_parser);
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
