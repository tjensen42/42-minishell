#include "exec.h"
#include "token.h"
#include <limits.h>
#include <fcntl.h>

static int	exec_redir_do(char *redir, char *file);
static int	exec_redir_process(char *redir, char *file, int type);
static int	exec_redir_get_num(char *redir, int type);
static int	exec_redir_open_file(char *file, int type);

int	exec_redir(t_list *l_token)
{
	t_list	*iter;
	char	*tmp;

	iter = l_token;
	while (iter && token_content(iter)->flags & TOK_REDIR && iter->next != NULL)
	{
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
	int	i;
	int	status;

	i = 0;
	while (ft_isdigit(redir[i]))
		i++;
	if (redir[i] == '>' && redir[i + 1] == '\0')
		status = exec_redir_process(redir, file, REDIR_OUT);
	else if (redir[i] == '>' && redir[i + 1] == '>')
		status = exec_redir_process(redir, file, REDIR_OUT_APP);
	else if (redir[i] == '<' && redir[i + 1] == '\0')
		status = exec_redir_process(redir, file, REDIR_IN);
	else if (redir[i] == '<' && redir[i + 1] == '<')
		status = exec_redir_process(redir, file, REDIR_HEREDOC);
	else
		status = ERROR;
	return (status);
}

static int exec_redir_process(char *redir, char *file, int type)
{
	int	fd[2];
	int	status;

	fd[REDIR_NUM] = exec_redir_get_num(redir, type);
	fd[REDIR_FILE] = exec_redir_open_file(file, type);
	if (fd[REDIR_NUM] == -1 || fd[REDIR_FILE] == -1)
		status = ERROR;
	if (status != ERROR)
	{
		if (dup2(fd[REDIR_FILE], fd[REDIR_NUM]) == -1)
		{
			print_error(SHELL_NAME, redir, NULL, strerror(errno));
			status = ERROR;
		}
	}
	if (fd[REDIR_FILE] != -1)
		close(fd[REDIR_FILE]);
	return (status);
}

static int	exec_redir_get_num(char *redir, int type)
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

static int exec_redir_open_file(char *file, int type)
{
	int	fd;

	fd = -2;
	if (type == REDIR_IN || type == REDIR_HEREDOC)
		fd = open(file, O_RDONLY, 0);
	else if (type == REDIR_OUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == REDIR_OUT_APP)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		print_error(SHELL_NAME, file, NULL, strerror(errno));
	return (fd);
}

// static int	exec_redir_in(char *redir, char *file, bool here_doc)
// {
// 	int	fd_num;
// 	int	fd_file;
// 	int	status;

// 	status = 0;
// 	fd_num = STDIN_FILENO;
// 	if (ft_isdigit(redir[0]))
// 		fd_num = exec_redir_get_num(redir);
// 	if (fd_num == -1)
// 		status = ERROR;
// 	if (here_doc)
// 		printf("HERE_DOC\n");
// 	else
// 		fd_file = open(file, O_RDONLY, 0);
// 	if (fd_file == -1)
// 		status = print_error(SHELL_NAME, file, NULL, strerror(errno));
// 	if (status != ERROR && dup2(fd_file, fd_num) == -1)
// 		status = print_error(SHELL_NAME, redir, NULL, strerror(errno));
// 	if (fd_file != -1)
// 		close(fd_file);
// 	return (status);
// }

// static int	exec_redir_out(char *redir, char *file, bool append)
// {
// 	int	fd_num;
// 	int	fd_file;
// 	int	status;

// 	status = 0;
// 	fd_num = STDOUT_FILENO;
// 	if (ft_isdigit(redir[0]))
// 		fd_num = exec_redir_get_num(redir);
// 	if (fd_num == -1)
// 		status = ERROR;
// 	if (append)
// 		fd_file = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	else
// 		fd_file = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd_file == -1)
// 		status = print_error(SHELL_NAME, file, NULL, strerror(errno));
// 	if (status != ERROR)
// 		if (dup2(fd_file, fd_num) == -1)
// 			status = print_error(SHELL_NAME, redir, NULL, strerror(errno));
// 	if (fd_file != -1)
// 		close(fd_file);
// 	return (status);
// }
