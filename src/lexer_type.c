#include "parser.h"

void	lexer_token_bin_op(char *str, int *i, t_list **l_token)
{
	t_list	*token;

	if ((str[*i] == '&' && str[*i + 1] == '&')
		|| (str[*i] == '|' && str[*i + 1] == '|'))
	{
		token = lexer_get_token(ft_substr(str, *i, 2), TOK_BIN_OP);
		ft_lstadd_back(l_token, token);
		*i += 2;
	}
}

void	lexer_token_redir(char *str, int *i, t_list **l_token)
{
	int		len;
	t_list	*token;

	len = 0;
	while (ft_isdigit(str[*i + len]))
		len++;
	if (str[*i + len] == '<' || str[*i + len] == '>')
	{
		if (str[*i + len] == str[*i + len + 1])
			len++;
		len++;
		token = lexer_get_token(ft_substr(str, *i, len), TOK_REDIR);
		ft_lstadd_back(l_token, token);
		*i += len;
	}
}

void	lexer_token_pipe(char *str, int *i, t_list **l_token)
{
	t_list	*token;

	if (str[*i] == '|')
	{
		token = lexer_get_token(ft_substr(str, *i, 1), TOK_PIPE);
		ft_lstadd_back(l_token, token);
		(*i)++;
	}
}

void	lexer_token_bracket(char *str, int *i, t_list **l_token)
{
	t_list	*token;

	if (str[*i] == ')' || str[*i] == '(')
	{
		token = lexer_get_token(ft_substr(str, *i, 1), TOK_BRACKET);
		ft_lstadd_back(l_token, token);
		(*i)++;
	}
}

int	lexer_token_text(char *str, int *i, t_list **l_token)
{
	int		len;
	t_list	*token;

	len = lexer_text_len(&str[*i]);
	if (len < 0)
		return (ERROR);
	if (len > 0)
	{
		token = lexer_get_token(ft_substr(str, *i, len), TOK_TEXT);
		ft_lstadd_back(l_token, token);
		*i += len;
		if (ft_strchr(WHITESPACES, str[*i]) == NULL && lexer_special_len(&str[*i]) == 0)
			token_content(token)->flags |= TOK_CONNECTED;
	}
	return (0);
}

int	lexer_token_quote(char *str, int *i, t_list **l_token)
{
	int		len;
	t_list	*token;

	len = lexer_quote_len(&str[*i]);
	if (len < 0)
		return (ERROR);
	if (len > 0)
	{
		if (str[*i] == '\'')
			token = lexer_get_token(ft_substr(str, *i + 1, len - 2), TOK_TEXT | TOK_S_QUOTE);
		else
			token = lexer_get_token(ft_substr(str, *i + 1, len - 2), TOK_TEXT | TOK_D_QUOTE);
		ft_lstadd_back(l_token, token);
		*i += len;
		if (ft_strchr(WHITESPACES, str[*i]) == NULL && lexer_special_len(&str[*i]) == 0)
			token_content(token)->flags |= TOK_CONNECTED;
	}
	return (0);
}
