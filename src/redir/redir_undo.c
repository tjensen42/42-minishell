/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_undo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:53:37 by hepple            #+#    #+#             */
/*   Updated: 2022/01/17 15:54:06 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

static t_list			*redir_undo_create(int fd_repl, int fd_repl_dup);
static t_c_redir_undo	*redir_undo_content(t_list *redir_undo);

int	redir_undo(t_list **l_undo)
{
	t_list	*iter;
	int		fd_repl;
	int		fd_repl_dup;
	int		status;

	status = 0;
	iter = *l_undo;
	while (iter)
	{
		fd_repl = redir_undo_content(iter)->fd_repl;
		fd_repl_dup = redir_undo_content(iter)->fd_repl_dup;
		if (fd_repl_dup == -1)
			close(fd_repl);
		else if (fd_repl_dup != -1)
		{
			if (dup2(fd_repl_dup, fd_repl) == -1)
				status = print_error_errno(SHELL_NAME, NULL, NULL);
			close(fd_repl_dup);
		}
		iter = iter->next;
	}
	ft_lstclear(l_undo, free);
	return (status);
}

int	redir_undo_add_fd(t_list **l_undo, int fd)
{
	t_list	*redir_undo;
	t_list	*iter;
	int		tmp;

	iter = *l_undo;
	while (iter)
	{
		if (redir_undo_content(iter)->fd_repl == fd)
			return (0);
		iter = iter->next;
	}
	tmp = dup(fd);
	if (tmp == -1 && errno != EBADF)
		return (print_error_errno(SHELL_NAME, NULL, NULL));
	else
	{
		redir_undo = redir_undo_create(fd, tmp);
		if (redir_undo == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		ft_lstadd_back(l_undo, redir_undo);
	}
	return (0);
}

static t_list	*redir_undo_create(int fd_repl, int fd_repl_dup)
{
	t_c_redir_undo	*redir_undo;

	redir_undo = malloc(sizeof(t_c_redir_undo));
	if (redir_undo == NULL)
		return (NULL);
	redir_undo->fd_repl = fd_repl;
	redir_undo->fd_repl_dup = fd_repl_dup;
	return (ft_lstnew(redir_undo));
}

static t_c_redir_undo	*redir_undo_content(t_list *redir_undo)
{
	return ((t_c_redir_undo *)(redir_undo->content));
}
