#include "parser.h"
#include "minishell.h"

char *minishell_get_line(void)
{
	char	*input;

	input = readline(PROMPT);
	if (input && input[0] != '\0')
		add_history(input);
	rl_on_new_line();
	return (input);
}

int	main(void)
{
	t_list	*l_token;
	char	*input;

	while (1)
	{
		input = minishell_get_line();
		l_token = lexer(input);
		parser(l_token);
	}
	return (0);
}

// void    sig_handler(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		printf("\b\b\n");
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// 	else if (signal == SIGQUIT)
// 	{
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// }
