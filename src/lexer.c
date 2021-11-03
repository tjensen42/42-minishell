#include "parser.h"
#include "minishell.h"

static int	lexer_general(char *str, int *i, t_list **lst);
static int	lexer_special(char *str, int *i, t_list **lst);

t_list	*lexer(char *input)
{
	int			i;
	int			status;
	t_list		*token_lst;

	token_lst = NULL;
	i = 0;
	while (input && input[i])
	{
		status = lexer_general(input, &i, &token_lst);
		if (status < 0)
		{
			ft_lstclear(&token_lst, lexer_destroy_token_content);
			printf("minishell: Syntax error: Unclosed quotation mark\n");
			return (NULL);
		}
		lexer_special(input, &i, &token_lst);
		while (input[i] && ft_strchr(" ", input[i]))
			i++;
	}
	return (token_lst);
}

int	lexer_general(char *str, int *i, t_list **lst)
{
	int		len;
	t_list	*token;

	len = lexer_general_len(&str[*i]);
	if (len < 0)
		return (ERROR);
	if (len > 0)
	{
		token = lexer_get_token(ft_substr(str, *i, len), TYPE_GENERAL);
		ft_lstadd_back(lst, token);
		*i += len;
	}
	return (0);
}

int	lexer_special(char *str, int *i, t_list **lst)
{
	int		len;
	t_list	*token;

	len = lexer_special_len(&str[*i]);
	if (len > 0)
	{
		token = lexer_get_token(ft_substr(str, *i, len), TYPE_SPECIAL);
		ft_lstadd_back(lst, token);
		*i += len;
	}
	return (0);
}
