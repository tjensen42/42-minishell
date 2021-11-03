#include "minishell.h"

# define TYPE_GENERAL	0
# define TYPE_SPECIAL	1
# define TYPE_QUOTE		2

# define WHITESPACES	" \t"
# define QUOT_MARKS		"\'\""

t_list *lexer_get_token(char *string, int type)
{
	t_token_content	*token_content;

	token_content = malloc(sizeof(t_token_content));
	if (token_content == NULL)
		return (NULL);
	token_content->string = string;
	token_content->type = type;
	return (ft_lstnew(token_content));
}

void	lexer_destroy_token_content(void *content)
{
	free(((t_token_content *)content)->string);
	((t_token_content *)content)->string = NULL;
	free(content);
}

int	lexer_special_len(char *chr)
{
	if (*chr == '(' || *chr == ')')
		return (1);
	else if (*chr == '<' && *(chr + 1) != '<')
		return (1);
	else if (*chr == '<' && *(chr + 1) == '<')
		return (2);
	else if (*chr == '>' && *(chr + 1) != '>')
		return (1);
	else if (*chr == '>' && *(chr + 1) == '>')
		return (2);
	else if (*chr == '|' && *(chr + 1) != '|')
		return (1);
	else if (*chr == '|' && *(chr + 1) == '|')
		return (2);
	else if (*chr == '&' && *(chr + 1) == '&')
		return (2);
	return (0);
}

int		lexer_quote_len(char *str)
{
	int 	i;
	char	mark;

	if (str == NULL || *str == '\0')
		return (0);
	if (ft_strchr(QUOT_MARKS, str[0]) == NULL)
		return (0);
	mark = str[0];
	i = 1;
	while (str[i])
	{
		if (str[i] == mark && str[i - 1] != '\\')
			break ;
		i++;
	}
	if (str[i] != mark)
		return (ERROR);
	return (i + 1);
}

int	lexer_general_len(char *str)
{
	int	i;
	int	quote_len;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(WHITESPACES, str[i]))
			break ;
		else if (lexer_special_len(&str[i]) > 0)
			break ;
		quote_len = lexer_quote_len(&str[i]);
		if (quote_len < 0)
			return (ERROR);
		if (quote_len == 0)
			i++;
		else
			i += quote_len;
	}
	return (i);
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
