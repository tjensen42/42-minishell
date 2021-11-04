#include "parser.h"
#include "minishell.h"

static int	lexer_text(char *str, int *i, t_list **l_token);
static int	lexer_check_brackets(t_list *l_token);

void	lexer_bin_op(char *str, int *i, t_list **l_token)
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

void	lexer_redir(char *str, int *i, t_list **l_token)
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

void	lexer_pipe(char *str, int *i, t_list **l_token)
{
	t_list	*token;

	if (str[*i] == '|')
	{
		token = lexer_get_token(ft_substr(str, *i, 1), TOK_PIPE);
		ft_lstadd_back(l_token, token);
		(*i)++;
	}
}

void	lexer_bracket(char *str, int *i, t_list **l_token)
{
	t_list	*token;

	if (str[*i] == ')' || str[*i] == '(')
	{
		token = lexer_get_token(ft_substr(str, *i, 1), TOK_BRACKET);
		ft_lstadd_back(l_token, token);
		(*i)++;
	}
}


t_list	*lexer(char *input)
{
	int			i;
	int			status;
	t_list		*l_token;

	l_token = NULL;
	i = 0;
	while (input && input[i])
	{
		lexer_bin_op(input, &i, &l_token);
		lexer_pipe(input, &i, &l_token);
		lexer_bracket(input, &i, &l_token);
		lexer_redir(input, &i, &l_token);
		status = lexer_text(input, &i, &l_token);
		if (status < 0)
		{
			ft_lstclear(&l_token, lexer_destroy_token_content);
			return (NULL);
		}
		while (input[i] && ft_strchr(" ", input[i]))
			i++;
	}
	if (lexer_check_brackets(l_token) == ERROR
		|| lexer_redir_mark_files(l_token) == ERROR)
	{
		ft_lstclear(&l_token, lexer_destroy_token_content);
		return (NULL);
	}
	return (l_token);
}

int	lexer_text(char *str, int *i, t_list **l_token)
{
	int		len;
	t_list	*token;

	len = lexer_general_len(&str[*i]);
	if (len < 0)
		return (ERROR);
	if (len > 0)
	{
		token = lexer_get_token(ft_substr(str, *i, len), TOK_TEXT);
		ft_lstadd_back(l_token, token);
		*i += len;
	}
	return (0);
}

static int	lexer_check_brackets(t_list *l_token)
{
	int	count;

	count = 0;
	while (l_token)
	{
		if (token_content(l_token)->type == TOK_BRACKET)
		{
			if ((token_content(l_token)->string)[0] == '(')
				count++;
			else if ((token_content(l_token)->string)[0] == ')')
				count--;
		}
		l_token = l_token->next;
	}
	if (count != 0)
	{
		if (count < 0)
			printf("minishell: Syntax error: Unopened brackets\n");
		else
			printf("minishell: Syntax error: Unclosed brackets\n");
		return (ERROR);
	}
	return (0);
}

int	lexer_redir_mark_files(t_list *l_token)
{
	while (l_token)
	{
		if (token_content(l_token)->type == TOK_REDIR)
		{
			if (l_token->next == NULL || token_content(l_token->next)->type != TOK_TEXT)
			{
				printf("minishell: Syntax error: Incomplete redirection\n");
				return (ERROR);
			}
			token_content(l_token->next)->type = TOK_REDIR_FILE;
		}
		l_token = l_token->next;
	}
	return (0);
}
