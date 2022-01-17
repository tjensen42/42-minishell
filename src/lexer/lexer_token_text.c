/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_text.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:41:54 by hepple            #+#    #+#             */
/*   Updated: 2022/01/17 16:10:17 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	text_len(char *str);
static int	quote_len(char *str);
static int	other_len(char *chr);

int	lexer_token_text(char *str, int *i, t_list **l_token)
{
	t_list	*token;
	char	*token_str;
	int		len;

	len = text_len(&str[*i]);
	if (len > 0)
	{
		token_str = ft_substr(str, *i, len);
		if (token_str == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		token = token_create(token_str, TOK_TEXT);
		if (token == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		ft_lstadd_back(l_token, token);
		*i += len;
		if (!ft_strchr(WHITESPACES, str[*i]) && other_len(&str[*i]) == 0)
			token_content(token)->flags |= TOK_CONNECTED;
	}
	return (0);
}

int	lexer_token_quote(char *str, int *i, t_list **l_token)
{
	t_list	*token;
	char	*token_str;
	int		len;

	len = quote_len(&str[*i]);
	if (len == ERROR)
		return (ERROR);
	if (len > 0)
	{
		token_str = ft_substr(str, *i + 1, len - 2);
		if (token_str == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		if (str[*i] == '\'')
			token = token_create(token_str, TOK_TEXT | TOK_S_QUOTE);
		else
			token = token_create(token_str, TOK_TEXT | TOK_D_QUOTE);
		if (token == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		ft_lstadd_back(l_token, token);
		*i += len;
		if (!ft_strchr(WHITESPACES, str[*i]) && other_len(&str[*i]) == 0)
			token_content(token)->flags |= TOK_CONNECTED;
	}
	return (0);
}

static int	text_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(WHITESPACES, str[i]))
			break ;
		else if (other_len(&str[i]) > 0)
			break ;
		else if (ft_strchr(QUOT_MARKS, str[i]))
			break ;
		i++;
	}
	return (i);
}

static int	quote_len(char *str)
{
	char	mark;
	int		i;

	if (str == NULL || *str == '\0')
		return (0);
	if (ft_strchr(QUOT_MARKS, str[0]) == NULL)
		return (0);
	mark = str[0];
	i = 1;
	while (str[i])
	{
		if (str[i] == mark)
			break ;
		i++;
	}
	if (str[i] != mark)
	{
		print_error(SHELL_NAME, ERR_SYNTAX, NULL, ERR_QUOTE);
		return (ERROR);
	}
	return (i + 1);
}

static int	other_len(char *chr)
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
