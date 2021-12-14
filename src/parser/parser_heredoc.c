#include "parser.h"
#include "redir.h"
#include <readline/readline.h>
#include <readline/history.h>

static char	*parser_read_heredoc(char *limiter);

int	parser_heredoc(t_list *l_token)
{
	char	*limiter;
	t_list	*redir_file;
	t_list	*iter;
	t_list	*tmp;

	if (l_token && redir_type(token_content(l_token)->string) == REDIR_HEREDOC)
	{
		redir_file = l_token->next;
		limiter = token_to_str(redir_file);
		if (limiter == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
		limiter = str_append_str(limiter, "\n");
		if (limiter == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
		free(token_content(redir_file)->string);
		token_content(redir_file)->flags |= TOK_HEREDOC;
		token_content(redir_file)->string = parser_read_heredoc(limiter);
		free(limiter);
		if (token_content(redir_file)->string == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
		iter = redir_file->next;
		while (iter && token_content(iter)->flags & TOK_REDIR_FILE)
		{
			if (token_content(iter)->flags & TOK_S_QUOTE)
				token_content(redir_file)->flags |= TOK_S_QUOTE;
			tmp = iter->next;
			lst_node_remove(&l_token, iter, c_token_destroy);
			iter = tmp;
		}
	}
	return (0);
}

// SIGNAL HANDLING ???
static char	*parser_read_heredoc(char *limiter)
{
	char	*tmp;
	char	*read_str;
	char	*here_str;

	here_str = ft_strdup("");
	if (here_str == NULL)
		return (NULL);
	write(1, "> ", 2);
	read_str = ft_get_next_line(STDIN_FILENO);
	while (read_str && ft_strncmp(read_str, limiter, ft_strlen(limiter) + 1))
	{
		tmp = here_str;
		here_str = ft_strjoin(here_str, read_str);
		if (here_str == NULL)
			break ;
		free(tmp);
		free(read_str);
		write(1, "> ", 2);
		read_str = ft_get_next_line(STDIN_FILENO);
	}
	free(read_str);
	return (here_str);
}
