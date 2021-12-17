#include "redir.h"

static t_c_redir_undo *redir_undo_content(t_list *redir_undo);
static int	redir_undo_add_fd(t_list **l_undo, int fd);
static int	redir_process(char *redir, char *file, t_list **l_undo);
static int	redir_fd(char *redir, int type);
static int	redir_open_file(char *file, int type, t_list **l_undo);
static t_list	*redir_undo_create(int fd_replaced, int fd_replaced_dup, char *here_doc);
static void	c_redir_undo_destroy(void *c_redir_undo);

int	redir(t_list *l_token, t_list **l_undo)
{
	char	*tmp;
	t_list	*iter;

	*l_undo = NULL;
	iter = l_token;
	while (iter && token_content(iter)->flags & TOK_REDIR && iter->next != NULL)
	{
		tmp = token_to_str(iter->next);
		if (tmp == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
		if (redir_process(token_content(iter)->string, tmp, l_undo) == ERROR)
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

static int redir_process(char *redir, char *file, t_list **l_undo)
{
	int	fd[2];
	int	status;
	int	type;

	status = 0;
	type = redir_type(redir);
	fd[REDIR_NUM] = redir_fd(redir, type);
	fd[REDIR_FILE] = redir_open_file(file, type, l_undo);
	if (fd[REDIR_NUM] == -1 || fd[REDIR_FILE] == -1)
		status = ERROR;
	if (status != ERROR)
	{
		if (redir_undo_add_fd(l_undo, fd[REDIR_NUM]) == ERROR)
			status = ERROR;
		if (status != ERROR && dup2(fd[REDIR_FILE], fd[REDIR_NUM]) == -1)
		{
			print_error(SHELL_NAME, redir, NULL, strerror(errno));
			status = ERROR;
		}
	}
	if (fd[REDIR_FILE] != -1)
		close(fd[REDIR_FILE]);
	return (status);
}

static int	redir_fd(char *redir, int type)
{
	int		i;
	long	fd;

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

static int redir_open_file(char *file, int type, t_list **l_undo)
{
	int			fd;
	char		*heredoc_file;
	char		*tmp;
	static int 	i = 0;

	fd = -2;
	if (type == REDIR_HEREDOC)
	{
		i++;
		tmp = ft_itoa(getpid());
		heredoc_file = ft_strjoin("tmp/", tmp);
		fd = open(heredoc_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			print_error(SHELL_NAME, "here_doc", NULL, strerror(errno));
		else
		{
			ft_lstadd_back(l_undo, redir_undo_create(-1, -1, ft_strdup(heredoc_file))); //protection
			write(fd, file, ft_strlen(file));
		}
		close(fd);
		fd = open(heredoc_file, O_RDONLY, 0);
		if (fd == -1)
			print_error(SHELL_NAME, "here_doc", NULL, strerror(errno));
		free(heredoc_file);
	}
	else if (type == REDIR_IN)
		fd = open(file, O_RDONLY, 0);
	else if (type == REDIR_OUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == REDIR_OUT_APP)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1 && type != REDIR_HEREDOC)
		print_error(SHELL_NAME, file, NULL, strerror(errno));
	return (fd);
}

static int		redir_undo_add_fd(t_list **l_undo, int fd)
{
	int		tmp;
	t_list	*iter;
	t_list	*redir_undo;

	iter = *l_undo;
	while (iter)
	{
		if (redir_undo_content(iter)->fd_replaced == fd)
			return (0);
		iter = iter->next;
	}
	errno = 0;
	tmp = dup(fd);
	if (tmp == -1 && errno != EBADF)
		return (print_error(SHELL_NAME, NULL, NULL, strerror(errno)));
	else
	{
		redir_undo = redir_undo_create(fd, tmp, NULL);
		if (redir_undo == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
		ft_lstadd_back(l_undo, redir_undo);
	}
	return (0);
}

static t_list	*redir_undo_create(int fd_replaced, int fd_replaced_dup, char *here_doc)
{
	t_c_redir_undo	*redir_undo;

	redir_undo = malloc(sizeof(t_c_redir_undo));
	if (redir_undo == NULL)
		return (NULL);
	redir_undo->fd_replaced = fd_replaced;
	redir_undo->fd_replaced_dup = fd_replaced_dup;
	redir_undo->here_doc_file = here_doc;
	return (ft_lstnew(redir_undo));
}

static void	c_redir_undo_destroy(void *c_redir_undo)
{
	free(((t_c_redir_undo *)c_redir_undo)->here_doc_file);
	((t_c_redir_undo *)c_redir_undo)->here_doc_file = NULL;
	free(c_redir_undo);
}

static t_c_redir_undo *redir_undo_content(t_list *redir_undo)
{
	return ((t_c_redir_undo *)(redir_undo->content));
}

int	redir_undo(t_list **l_undo)
{
	int		status;
	int		fd_replaced;
	int		fd_replaced_dup;
	t_list	*iter;

	status = 0;
	iter = *l_undo;
	while (iter)
	{
		fd_replaced = redir_undo_content(iter)->fd_replaced;
		fd_replaced_dup = redir_undo_content(iter)->fd_replaced_dup;
		if (redir_undo_content(iter)->here_doc_file)
		{
			if (unlink(redir_undo_content(iter)->here_doc_file) == -1)
				status = print_error(SHELL_NAME, "here_doc", "unlink", strerror(errno));
		}
		else if (fd_replaced_dup == -1)
			close(fd_replaced);
		else if (fd_replaced_dup != -1)
		{
			if (dup2(fd_replaced_dup, fd_replaced) == -1)
				status = print_error(SHELL_NAME, NULL, NULL, strerror(errno));
			close(fd_replaced_dup);
		}
		iter = iter->next;
	}
	ft_lstclear(l_undo, c_redir_undo_destroy);
	return (status);
}
