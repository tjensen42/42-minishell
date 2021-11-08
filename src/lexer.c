#include "parser.h"
#include "minishell.h"

static t_list *lexer_token_list_get(char *input);
static int	lexer_check_brackets(t_list *l_token);
static int	lexer_redir_mark_files(t_list *l_token);

t_list	*lexer(char *input)
{
	t_list		*l_token;

	l_token = lexer_token_list_get(input);
	if (l_token == NULL)
		return (NULL);
	if (lexer_check_brackets(l_token) == ERROR)
	{
		ft_lstclear(&l_token, lexer_c_token_destroy);
		return (NULL);
	}
	if (lexer_redir_mark_files(l_token) == ERROR)
	{
		ft_lstclear(&l_token, lexer_c_token_destroy);
		return (NULL);
	}
	lexer_printer(l_token);
	return (l_token);
}

static t_list *lexer_token_list_get(char *input)
{
	int		i;
	int		status;
	t_list	*l_token;

	l_token = NULL;
	i = 0;
	while (input && input[i])
	{
		lexer_token_bin_op(input, &i, &l_token);
		lexer_token_pipe(input, &i, &l_token);
		lexer_token_bracket(input, &i, &l_token);
		lexer_token_redir(input, &i, &l_token);
		lexer_token_text(input, &i, &l_token);
		status = lexer_token_quote(input, &i, &l_token);
		if (status < 0)
		{
			ft_lstclear(&l_token, lexer_c_token_destroy);
			return (NULL);
		}
		while (input[i] && ft_strchr(WHITESPACES, input[i]))
			i++;
	}
	return (l_token);
}

static int	lexer_check_brackets(t_list *l_token)
{
	int	count;

	count = 0;
	while (l_token)
	{
		if (token_content(l_token)->flags & TOK_BRACKET)
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
			print_error(ERR_UNO_BRACKET);
		else
			print_error(ERR_UNC_BRACKET);
		return (ERROR);
	}
	return (0);
}

static int	lexer_redir_mark_files(t_list *l_token)
{
	while (l_token)
	{
		if (token_content(l_token)->flags & TOK_REDIR)
		{
			if (l_token->next == NULL
				|| !(token_content(l_token->next)->flags & TOK_TEXT))
			{
				print_error(ERR_REDIR);
				return (ERROR);
			}
			token_content(l_token->next)->flags |= TOK_REDIR_FILE;
		}
		l_token = l_token->next;
	}
	return (0);
}
