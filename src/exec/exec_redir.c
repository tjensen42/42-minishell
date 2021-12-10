#include "exec.h"
#include "token.h"
#include <limits.h>
#include <fcntl.h>

static int	exec_redir_do(char *redir, char *file);
static int	exec_redir_in(char *redir, char *file, bool here_doc);
static int	exec_redir_out(char *redir, char *file, bool append);
static int	exec_redir_get_fd(char *redir);

int	exec_redir(t_list *l_token)
{
	t_list	*iter;
	char	*tmp;

	iter = l_token;
	while (iter && token_content(iter)->flags & TOK_REDIR)
	{
		if (iter->next == NULL)
			break ;
		tmp = l_token_to_str(iter->next);
		if (tmp == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
		if (exec_redir_do(token_content(iter)->string, tmp) == ERROR)
		{
			free(tmp);
			return (ERROR);
		}
		free(tmp);
		iter = iter->next->next;
	}
	if (iter != NULL)
		return (print_error(SHELL_NAME, NULL, NULL, "ambiguous redirection"));
	return (0);
}

static int	exec_redir_do(char *redir, char *file)
{
	int	status;
	int	i;

	i = 0;
	while (ft_isdigit(redir[i]))
		i++;
	if (redir[i] == '>' && redir[i + 1] == '\0')
		status = exec_redir_out(redir, file, false);
	else if (redir[i] == '>' && redir[i + 1] == '>')
		status = exec_redir_out(redir, file, true);
	else if (redir[i] == '<' && redir[i + 1] == '\0')
		status = exec_redir_in(redir, file, false);
	else if (redir[i] == '<' && redir[i + 1] == '<')
		status = exec_redir_in(redir, file, true);
	else
		status = ERROR;
	return (status);
}

static int	exec_redir_in(char *redir, char *file, bool here_doc)
{
	int	fd_num;
	int	fd_file;
	int	status;

	status = 0;
	if (ft_isdigit(redir[0]))
		fd_num = exec_redir_get_fd(redir);
	else
		fd_num = STDIN_FILENO;
	if (fd_num == -1)
		status = ERROR;
	if (here_doc)
		printf("HERE_DOC\n");
	else
		fd_file = open(file, O_RDONLY, 0);
	if (fd_file == -1)
		status = print_error(SHELL_NAME, file, NULL, strerror(errno));
	if (status != ERROR && dup2(fd_file, fd_num) == -1)
		status = print_error(SHELL_NAME, redir, NULL, strerror(errno));
	if (fd_file != -1)
		close(fd_file);
	return (status);
}

static int	exec_redir_out(char *redir, char *file, bool append)
{
	int	fd_num;
	int	fd_file;
	int	status;

	status = 0;
	if (ft_isdigit(redir[0]))
		fd_num = exec_redir_get_fd(redir);
	else
		fd_num = STDOUT_FILENO;
	if (fd_num == -1)
		status = ERROR;
	if (append)
		fd_file = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd_file = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_file == -1)
		status = print_error(SHELL_NAME, file, NULL, strerror(errno));
	if (status != ERROR && dup2(fd_file, fd_num) == -1)
		status = print_error(SHELL_NAME, redir, NULL, strerror(errno));
	if (fd_file != -1)
		close(fd_file);
	return (status);
}

static int	exec_redir_get_fd(char *redir)
{
	long	fd;
	int		i;

	fd = 0;
	i = 0;
	while (ft_isdigit(redir[i]))
	{
		fd = fd * 10 + (redir[i] - '0');
		if (fd > INT_MAX)
			return (print_error(SHELL_NAME, redir, NULL, "file descriptor out of range"));
		i++;
	}
	return ((int) fd);
}
