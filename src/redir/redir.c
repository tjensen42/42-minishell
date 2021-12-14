#include "redir.h"

static int	redir_process(char *redir, char *file, bool is_builtin);
static int	redir_fd(char *redir, int type);
static int	redir_open_file(char *file, int type);

int	redir(t_list *l_token, bool is_builtin)
{
	char	*tmp;
	t_list	*iter;

	iter = l_token;
	while (iter && token_content(iter)->flags & TOK_REDIR && iter->next != NULL)
	{
		tmp = token_to_str(iter->next);
		if (tmp == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
		if (redir_process(token_content(iter)->string, tmp, is_builtin) == ERROR)
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

static int redir_process(char *redir, char *file, bool is_builtin)
{
	int	fd[2];
	int	status;
	int	type;

	type = redir_type(redir);
	fd[REDIR_NUM] = redir_fd(redir, type);
	if (is_builtin && fd[REDIR_NUM] > STDERR_FILENO)
		return (0);
	fd[REDIR_FILE] = redir_open_file(file, type);
	if (fd[REDIR_NUM] == -1 || fd[REDIR_FILE] == -1)
		status = ERROR;
	if (status != ERROR && dup2(fd[REDIR_FILE], fd[REDIR_NUM]) == -1)
	{
		print_error(SHELL_NAME, redir, NULL, strerror(errno));
		status = ERROR;
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

static int redir_open_file(char *file, int type)
{
	int		fd;
	char	*heredoc_file;

	fd = -2;
	if (type == REDIR_HEREDOC)
	{
		heredoc_file = "tmp/1";
		fd = open(heredoc_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			print_error(SHELL_NAME, "here_doc", NULL, strerror(errno));
		else
			write(fd, file, ft_strlen(file));
		close(fd);
		fd = open(heredoc_file, O_RDONLY, 0);
		if (fd == -1)
			print_error(SHELL_NAME, "here_doc", NULL, strerror(errno));
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
