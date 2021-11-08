#include "parser.h"
#include "minishell.h"

char *minishell_get_line(void);

int	main(void)
{
	t_list	*l_token;
	t_list	*l_parse;
	char	*input;

	while (1)
	{
		input = minishell_get_line();
		l_token = lexer(input);
		if (l_token != NULL)
		{
			l_parse = parser(l_token);
			ft_lstclear(&l_token, lexer_c_token_destroy);
//			if (l_parse != NULL)
//				expander(l_parse);
		}
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
