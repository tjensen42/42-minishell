#include "redir.h"

static t_c_redir_undo	*redir_undo_content(t_list *redir_undo);
static t_list			*redir_undo_create(int fd_repl, int fd_repl_dup);

int	redir_undo(t_list **l_undo)
{
	int		status;
	int		fd_repl;
	int		fd_repl_dup;
	t_list	*iter;

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
				status = print_error(SHELL_NAME, NULL, NULL, strerror(errno));
			close(fd_repl_dup);
		}
		iter = iter->next;
	}
	ft_lstclear(l_undo, free);
	return (status);
}

int	redir_undo_add_fd(t_list **l_undo, int fd)
{
	int		tmp;
	t_list	*iter;
	t_list	*redir_undo;

	iter = *l_undo;
	while (iter)
	{
		if (redir_undo_content(iter)->fd_repl == fd)
			return (0);
		iter = iter->next;
	}
	errno = 0;
	tmp = dup(fd);
	if (tmp == -1 && errno != EBADF)
		return (print_error(SHELL_NAME, NULL, NULL, strerror(errno)));
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
