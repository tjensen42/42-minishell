#include "lexer.h"
#include "parser.h"
#include "minishell.h"
#include "printer.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*minishell_get_line(void);
int		minishell_process_input(char *input);

int	main(int argc, char *argv[])
{
	char	*input;

	if (argc == 2 && argv[1])
		minishell_process_input(argv[1]);
	else
	{
		while (1)
		{
			input = minishell_get_line();
			minishell_process_input(input);
		}
	}
	return (0);
}

int	minishell_process_input(char *input)
{
	t_list	*l_token;
	t_list	*l_parser;

	l_token = NULL;
	l_parser = NULL;
	l_token = lexer(input);
	if (l_token != NULL)
		l_parser = parser(l_token);
	//
	printf("\n\n");
	//
	if (l_token != NULL && l_parser != NULL)
		execution_wrapper(l_parser);
	ft_lstclear(&l_parser, c_cmd_destroy);
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
