/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:53:06 by hepple            #+#    #+#             */
/*   Updated: 2022/01/17 15:53:30 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include "redir.h"

static int	redir_process(char *redir, char *file, t_list **l_undo);
static int	redir_fd(char *redir, int type);
static int	redir_open_file(char *file, int type);

int	redir(t_list *l_token, t_list **l_undo)
{
	t_list	*iter;
	char	*tmp;

	if (l_undo)
		*l_undo = NULL;
	iter = l_token;
	while (iter && token_content(iter)->flags & TOK_REDIR && iter->next != NULL)
	{
		tmp = token_to_str(iter->next);
		if (tmp == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		if (redir_process(token_content(iter)->str, tmp, l_undo) == ERROR)
		{
			free(tmp);
			return (ERROR);
		}
		free(tmp);
		iter = iter->next;
		while (iter && token_content(iter)->flags & TOK_CONNECTED)
			iter = iter->next;
		iter = iter->next;
	}
	if (iter != NULL)
		return (print_error(SHELL_NAME, NULL, NULL, "ambiguous redirection"));
	return (0);
}

int	redir_type(char *redir)
{
	int	i;

	if (redir == NULL)
		return (ERROR);
	i = 0;
	while (ft_isdigit(redir[i]))
		i++;
	if (redir[i] == '>' && redir[i + 1] == '\0')
		return (REDIR_OUT);
	else if (redir[i] == '>' && redir[i + 1] == '>')
		return (REDIR_OUT_APP);
	else if (redir[i] == '<' && redir[i + 1] == '\0')
		return (REDIR_IN);
	else if (redir[i] == '<' && redir[i + 1] == '<')
		return (REDIR_HEREDOC);
	else
		return (ERROR);
}

static int	redir_process(char *redir, char *file, t_list **l_undo)
{
	int	fd[2];
	int	type;
	int	status;

	status = 0;
	type = redir_type(redir);
	fd[REDIR_NUM] = redir_fd(redir, type);
	fd[REDIR_FILE] = redir_open_file(file, type);
	if (fd[REDIR_NUM] == -1 || fd[REDIR_FILE] == -1)
		status = ERROR;
	if (status != ERROR)
	{
		if (l_undo && redir_undo_add_fd(l_undo, fd[REDIR_NUM]) == ERROR)
			status = ERROR;
		if (status != ERROR && dup2(fd[REDIR_FILE], fd[REDIR_NUM]) == -1)
			status = print_error_errno(SHELL_NAME, redir, NULL);
	}
	if (fd[REDIR_FILE] != -1)
		close(fd[REDIR_FILE]);
	return (status);
}

static int	redir_fd(char *redir, int type)
{
	long	fd;
	int		i;

	fd = 0;
	i = 0;
	if (ft_isdigit(redir[0]))
	{
		while (ft_isdigit(redir[i]))
		{
			fd = fd * 10 + (redir[i] - '0');
			if (fd > INT_MAX)
			{
				print_error(SHELL_NAME, redir, NULL,
					"file descriptor out of range");
				return (ERROR);
			}
			i++;
		}
		return ((int) fd);
	}
	else if (type == REDIR_OUT || type == REDIR_OUT_APP)
		return (STDOUT_FILENO);
	else if (type == REDIR_IN || type == REDIR_HEREDOC)
		return (STDIN_FILENO);
	return (ERROR);
}

static int	redir_open_file(char *file, int type)
{
	int	fd[2];

	if (type == REDIR_HEREDOC)
	{
		if (pipe(fd) == -1)
			fd[0] = -1;
		else
		{
			write(fd[1], file, ft_strlen(file));
			close(fd[1]);
		}
	}
	else if (type == REDIR_IN)
		fd[0] = open(file, O_RDONLY, 0);
	else if (type == REDIR_OUT)
		fd[0] = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == REDIR_OUT_APP)
		fd[0] = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd[0] == -1)
		print_error_errno(SHELL_NAME, file, NULL);
	return (fd[0]);
}
