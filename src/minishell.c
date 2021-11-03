#include "minishell.h"

char *input_get(void);

int	main(void)
{
	t_list	*token_lst;
	char	*input;

	while (1)
	{
		input = input_get();
		//printf("%s\n", input);
		token_lst = lexer(input);
		if (token_lst == NULL)
			return (1);
		while (token_lst->next != NULL)
		{
			printf("%s : ", ((t_token *)(token_lst->content))->string);
			token_lst = token_lst->next;
		}
		printf("%s\n", ((t_token *)(token_lst->content))->string);
	}

	return (0);
}

char *input_get(void)
{
	char	*input;

	input = readline(PROMPT);
	if (input && input[0] != '\0')
		add_history(input);
	rl_on_new_line();
	return (input);
}
