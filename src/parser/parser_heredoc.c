/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:44:03 by hepple            #+#    #+#             */
/*   Updated: 2022/01/17 16:11:07 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>

#include "parser.h"
#include "redir.h"
#include "signals.h"

static int	heredoc_processing(t_list *redir_file, char **limiter);
static char	*heredoc_readline(char *limiter);
static char	*heredoc_gnl(char **limiter);
static void	heredoc_merge(t_list *redir_file, t_list **l_token);

int	parser_heredoc(t_list *l_token)
{
	t_list	*redir_file;
	char	*limiter;

	if (l_token && redir_type(token_content(l_token)->str) == REDIR_HEREDOC)
	{
		redir_file = l_token->next;
		limiter = token_to_str(redir_file);
		if (limiter == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		if (heredoc_processing(redir_file, &limiter) == ERROR)
		{
			free(limiter);
			return (ERROR);
		}
		free(limiter);
		token_content(redir_file)->flags |= TOK_HEREDOC;
		heredoc_merge(redir_file, &l_token);
	}
	return (0);
}

static int	heredoc_processing(t_list *redir_file, char **limiter)
{
	int	fd;

	fd = dup(STDIN_FILENO);
	if (fd == -1)
		return (print_error_errno(SHELL_NAME, NULL, NULL));
	free(token_content(redir_file)->str);
	if (isatty(STDIN_FILENO))
		token_content(redir_file)->str = heredoc_readline(*limiter);
	else
		token_content(redir_file)->str = heredoc_gnl(limiter);
	if (errno == EBADF)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			print_error_errno(SHELL_NAME, NULL, NULL);
		close(fd);
		return (ERROR);
	}
	close(fd);
	if (token_content(redir_file)->str == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
	return (0);
}

static char	*heredoc_readline(char *limiter)
{
	char	*read_str;
	char	*here_str;

	signal(SIGINT, signal_ctlc_heredoc);
	here_str = ft_strdup("");
	if (here_str == NULL)
		return (NULL);
	read_str = readline("> ");
	while (read_str && ft_strncmp(read_str, limiter, ft_strlen(limiter) + 1))
	{
		read_str = str_append_chr(read_str, '\n');
		if (read_str == NULL)
		{
			free(here_str);
			print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM));
			return (NULL);
		}
		here_str = str_append_str(here_str, read_str);
		if (here_str == NULL)
			break ;
		free(read_str);
		read_str = readline("> ");
	}
	free(read_str);
	return (here_str);
}

static char	*heredoc_gnl(char **limiter)
{
	char	*read_str;
	char	*here_str;

	signal(SIGINT, signal_ctlc_heredoc);
	*limiter = str_append_chr(*limiter, '\n');
	if (*limiter == NULL)
		return (NULL);
	here_str = ft_strdup("");
	if (here_str == NULL)
		return (NULL);
	read_str = minishell_get_next_line(STDIN_FILENO);
	while (read_str && ft_strncmp(read_str, *limiter, ft_strlen(*limiter) + 1))
	{
		here_str = str_append_str(here_str, read_str);
		if (here_str == NULL)
			break ;
		free(read_str);
		read_str = minishell_get_next_line(STDIN_FILENO);
	}
	free(read_str);
	return (here_str);
}

static void	heredoc_merge(t_list *redir_file, t_list **l_token)
{
	t_list	*iter;
	t_list	*tmp;

	if (token_content(redir_file)->flags & TOK_CONNECTED)
	{
		token_content(redir_file)->flags &= ~(TOK_CONNECTED);
		iter = redir_file->next;
		while (iter && token_content(iter)->flags & TOK_CONNECTED)
		{
			if (token_content(iter)->flags & TOK_S_QUOTE)
				token_content(redir_file)->flags |= TOK_S_QUOTE;
			if (token_content(iter)->flags & TOK_D_QUOTE)
				token_content(redir_file)->flags |= TOK_D_QUOTE;
			tmp = iter->next;
			lst_node_remove(l_token, iter, c_token_destroy);
			iter = tmp;
		}
		if (token_content(iter)->flags & TOK_S_QUOTE)
			token_content(redir_file)->flags |= TOK_S_QUOTE;
		if (token_content(iter)->flags & TOK_D_QUOTE)
			token_content(redir_file)->flags |= TOK_D_QUOTE;
		lst_node_remove(l_token, iter, c_token_destroy);
	}
}
