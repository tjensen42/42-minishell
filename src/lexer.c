#include "minishell.h"

# define TYPE_GENERAL	0
# define TYPE_SPECIAL	1
# define TYPE_QUOTE		2

// # define TYPE_PIPE		1
// # define TYPE_OR		2
// # define TYPE_AND		3
// # define TYPE_REDIR		4
// # define TYPE_D_QUOTE	6
// # define TYPE_O_BRACKET	7
// # define TYPE_C_BRACKET	8
// # define TYPE_SPACE		9

int	lexer_special_chr_check(char *chr)
{
	if (*chr == ' ')
		return (1);
	else if (*chr == '(' || *chr == ')')
		return (1);
	else if (*chr == '<' || *chr == '>')
		return (1);
	else if (*chr == '|' && *(chr + 1) != '|')
		return (1);
	else if (*chr == '|' && *(chr + 1) == '|')
		return (2);
	else if (*chr == '&' && *(chr + 1) == '&')
		return (2);
	return (-1);
}

int		lexer_quote_len(char *str)
{
	int 	i;
	char	quote;

	if (str[0] != '\'' && str[0] != '\"')
		return (0);
	quote = str[0];
	i = 1;
	while (str[i])
	{
		if (str[i] == quote && str[i - 1] != '\\')
			break ;
		i++;
	}
	if (str[i] == quote)
		return (i + 1);
	return (-1);
}

int	lexer_general_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (lexer_special_chr_check(&str[i]) > 0)
			break ;
		else if (str[i] == '\'' || str[i] == '\"')
			break ;
		i++;
	}
	return (i);
}

t_list *lexer_get_token(char *string, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->string = string;
	token->type = type;
	return (ft_lstnew(token));
}

int	lexer_quote_chr(char *str, int *i, t_list **lst)
{
	int		len;
	int		tmp1;
	int		tmp2;
	t_list	*token;

	len = 0;
	tmp1 = 1;
	tmp2 = 1;
	while (tmp1 > 0 || tmp2 > 0)
	{
		tmp1 = lexer_quote_len(&str[*i + len]);
		if (tmp1 > 0)
			len += tmp1;
		tmp2 = lexer_general_len(&str[*i + len]);
		if (tmp2 > 0)
			len += tmp2;
	}
	if (len > 0)
	{
		token = lexer_get_token(ft_substr(str, *i, len), TYPE_QUOTE);
		ft_lstadd_back(lst, token);
		*i += len;
		return (0);
	}
	return (len);
}

int	lexer_special_chr(char *str, int *i, t_list **lst)
{
	int		len;
	t_list	*token;

	len = lexer_special_chr_check(&str[*i]);
	if (len > 0)
	{
		token = lexer_get_token(ft_substr(str, *i, len), TYPE_SPECIAL);
		ft_lstadd_back(lst, token);
		*i += len;
	}
	return (0);
}

int	lexer_general_chr(char *str, int *i, t_list **lst)
{
	int		len;
	t_list	*token;

	len = lexer_general_len(&str[*i]);
	len += lexer_quote_len(&str[*i + len]);
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

	status = 0;
	token_lst = NULL;
	i = 0;
	while (i < (int)ft_strlen(input))
	{
		status = lexer_quote_chr(input, &i, &token_lst);
		if (status < 0)
			break ;
		status = lexer_special_chr(input, &i, &token_lst);
		if (status < 0)
			break ;
		status = lexer_general_chr(input, &i, &token_lst);
		if (status < 0)
			break ;
		while (input[i] == ' ')
			i++;
	}
	if (status < 0)
	{
		ft_lstclear(&token_lst, free);
		printf("Syntax error\n");
	}
	return (token_lst);
}
