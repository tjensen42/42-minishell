#include "lexer.h"
#include "printer.h"

static t_list	*lexer_token_list_get(char *input);
static int		lexer_redir_mark_files(t_list *l_token);

t_list	*lexer(char *input)
{
	t_list		*l_token;

	l_token = lexer_token_list_get(input);
	if (l_token == NULL)
		return (NULL);
	if (lexer_syntax_check(l_token) == ERROR)
	{
		ft_lstclear(&l_token, c_token_destroy);
		return (NULL);
	}
	if (lexer_redir_mark_files(l_token) == ERROR)
	{
		ft_lstclear(&l_token, c_token_destroy);
		return (NULL);
	}
	printer_token(l_token);
	return (l_token);
}

static t_list	*lexer_token_list_get(char *input)
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
			ft_lstclear(&l_token, c_token_destroy);
			return (NULL);
		}
		while (input[i] && ft_strchr(WHITESPACES, input[i]))
			i++;
	}
	return (l_token);
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
			l_token = l_token->next;
			token_content(l_token)->flags |= TOK_REDIR_FILE;
			while (token_content(l_token)->flags & TOK_CONNECTED)
			{
				token_content(l_token->next)->flags |= TOK_REDIR_FILE;
				l_token = l_token->next;
			}
		}
		l_token = l_token->next;
	}
	return (0);
}