#include "parser.h"

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
	{
		printf("minishell: Syntax error: Unclosed quotation mark\n");
		return (ERROR);
	}
	return (i + 1);
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
