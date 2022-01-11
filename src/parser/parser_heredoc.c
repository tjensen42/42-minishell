#include "parser.h"
#include "redir.h"
#include "signals.h"

static char	*parser_heredoc_read(char *limiter);
static void	parser_heredoc_merge(t_list *redir_file, t_list **l_token);

int	parser_heredoc(t_list *l_token)
{
	char	*limiter;
	t_list	*redir_file;
	int		fd;

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
		fd = dup(STDIN_FILENO);
		token_content(redir_file)->string = parser_heredoc_read(limiter);
		if (errno == EBADF)
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
			return (ERROR);
		}
		close(fd);
		free(limiter);
		if (token_content(redir_file)->string == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
		parser_heredoc_merge(redir_file, &l_token);
	}
	return (0);
}

static char	*parser_heredoc_read(char *limiter)
{
	char	*tmp;
	char	*read_str;
	char	*here_str;

	signal(SIGINT, signal_ctlc_heredoc);
	here_str = ft_strdup("");
	if (here_str == NULL)
		return (NULL);
	if (isatty(STDIN_FILENO))
		write(1, "> ", 2);
	errno = 0;
	read_str = ft_get_next_line(STDIN_FILENO);
	while (read_str && ft_strncmp(read_str, limiter, ft_strlen(limiter) + 1))
	{
		tmp = here_str;
		here_str = ft_strjoin(here_str, read_str);
		if (here_str == NULL)
			break ;
		free(tmp);
		if (isatty(STDIN_FILENO))
			write(1, "> ", 2);
		free(read_str);
		read_str = ft_get_next_line(STDIN_FILENO);
	}
	free(read_str);
	return (here_str);
}

static void	parser_heredoc_merge(t_list *redir_file, t_list **l_token)
{
	t_list	*tmp;
	t_list	*iter;

	if (token_content(redir_file)->flags & TOK_CONNECTED)
	{
		token_content(redir_file)->flags &= ~(TOK_CONNECTED);
		iter = redir_file->next;
		while (iter && token_content(iter)->flags & TOK_CONNECTED)
		{
			if (token_content(iter)->flags & TOK_S_QUOTE)
				token_content(redir_file)->flags |= TOK_S_QUOTE;
			tmp = iter->next;
			lst_node_remove(l_token, iter, c_token_destroy);
			iter = tmp;
		}
		if (token_content(iter)->flags & TOK_S_QUOTE)
			token_content(redir_file)->flags |= TOK_S_QUOTE;
		lst_node_remove(l_token, iter, c_token_destroy);
	}
}
