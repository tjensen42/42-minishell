#include "minishell.h"

char *input_get(void);

char *input_get(void)
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
	t_list	*token_lst;
	char	*input;

	while (1)
	{
		input = input_get();
		token_lst = lexer(input);

		if (token_lst != NULL)
		{
			while (token_lst->next != NULL)
			{
				printf("%s : ", ((t_token_content *)(token_lst->content))->string);
				token_lst = token_lst->next;
			}
			printf("%s\n", ((t_token_content *)(token_lst->content))->string);
			ft_lstclear(&token_lst, lexer_destroy_token_content);
		}
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
