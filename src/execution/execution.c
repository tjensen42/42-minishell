#include "parser.h"
#include "minishell.h"
#include "printer.h"
#include "cmd.h"
#include "builtin.h"
#include "execution.h"

#include <sys/types.h>
#include <sys/wait.h>

static int	execution_pipeline(t_list *pipeline);
static void	execution_pipeline_element(t_list *element, int pipes[2][2], int i, bool last);
static int	execution_scmd(t_list *scmd, bool pipeline);
static void	pipes_init(int pipes[2][2]);
static int	close_pipe_end(int pipe_end);
static void	child_set_pipes(int fd[2], int pipes[2][2], int i, bool last);
static int	close_pipes(int	pipes[2][2], int i, bool last);
static char	**list_to_split(t_list *l_token);

static void	environ_path_append_slash(char **paths)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		if (paths[i][ft_strlen(paths[i]) - 1] != '/')
		{
			tmp = paths[i];
			paths[i] = ft_strjoin(paths[i], "/");
			free(tmp);
			tmp = NULL;
		}
		i++;
	}
}

static char	**environ_path_get(void)
{
	int			i;
	char		**paths;
	extern char	**environ;

	if (environ == NULL)
		return (NULL);
	paths = NULL;
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
		{
			paths = ft_split((environ[i] + 5), ':');
			if (paths == NULL)
				return (NULL);
			environ_path_append_slash(paths);
			break ;
		}
		i++;
	}
	return (paths);
}

static int	pipex_cmd_set_path(char **cmd)
{
	int		i;
	char	*cmd_tmp;
	char	**paths;

	if (access(*cmd, F_OK) == 0)
		return (0);
	paths = environ_path_get();
	if (paths == NULL)
		return (ERROR);
	i = 0;
	while (paths[i])
	{
		cmd_tmp = ft_strjoin(paths[i], *cmd);
		if (access(cmd_tmp, F_OK) == 0)
		{
			free(*cmd);
			*cmd = cmd_tmp;
			ft_free_split(&paths);
			return (0);
		}
		free(cmd_tmp);
		i++;
	}
	ft_free_split(&paths);
	return (127);
}






int	execution_recursive(t_list *l_cmd)
{
	int	pid;
	int	status;

	pid = 0;
	status = 0;
	if (cmd_type(l_cmd) == CMD_SCMD)
		status = execution_scmd(l_cmd, false);
	else if (cmd_type(l_cmd) == CMD_PIPELINE)
		status = execution_pipeline(l_cmd);
	else if (cmd_type(l_cmd) == CMD_GROUP)
	{
		pid = fork();
		if (pid == 0)
			exit(execution_recursive(cmd_content(l_cmd)->l_element));
		waitpid(pid, &status, 0);
		status = WEXITSTATUS(status);
	}
	if (l_cmd->next)
	{
		l_cmd = l_cmd->next;
		while (((cmd_content(l_cmd)->type & CMD_AND) && status != 0)
				|| ((cmd_content(l_cmd)->type & CMD_OR) && status == 0))
		{
			l_cmd = l_cmd->next->next;
			if (l_cmd == NULL)
				return (status);
		}
		status = execution_recursive(l_cmd->next);
	}
	return (status);
}

static int	execution_pipeline(t_list *pipeline)
{
	int		i;
	int		pid;
	int		status;
	int		pipes[2][2];
	t_list	*iter;

	pipes_init(pipes);
	i = 0;
	iter = cmd_content(pipeline)->l_element;
	while (iter)
	{
		if (iter->next && pipe(pipes[i % 2]) < 0)
			return (print_error("Too many open files.")); // close all pipes, free and exit
		pid = fork();
		if (pid < 0)
			return (print_error("FORK fail"));
		if (pid == 0)
			execution_pipeline_element(iter, pipes, i, (iter->next == NULL));
		close_pipes(pipes, i, (iter->next == NULL));
		iter = iter->next;
		i++;
	}
	waitpid(pid, &status, 0);
	while (wait(NULL) >= 0);
	return (WEXITSTATUS(status));
}

static void	execution_pipeline_element(t_list *element, int pipes[2][2], int i, bool last)
{
	int		fd[2];

	child_set_pipes(fd, pipes, i, last);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close_pipes(pipes, -1, false);
	if (cmd_type(element) == CMD_SCMD)
		execution_scmd(element, true);
	else if (cmd_type(element) == CMD_GROUP)
		exit(execution_recursive(cmd_content(element)->l_element));
}

static int	execution_scmd(t_list *scmd, bool pipeline)
{
	int			pid;
	int			status;
	char		**argv;
	t_c_scmd	*c_scmd;

	c_scmd = scmd_content(scmd);
	// Variable expansion
	// Wildcard expansion
	// Redir processing
	argv = list_to_split(c_scmd->l_argv);
	//builtin check
	pid = 0;
	if (!pipeline)
		pid = fork();
	if (pid == 0 || pipeline)
	{
		if (pipex_cmd_set_path(argv) != 0)
		{
			write(2, argv[0], ft_strlen(argv[0]));
			print_error(": command not found");
			ft_free_split(&argv);
			exit(127);
		}
		execve(argv[0], argv, g_env);
		print_error("Error execve");
		ft_free_split(&argv);
		exit(ERROR);
	}
	waitpid(pid, &status, 0);
	status = WEXITSTATUS(status);
	return (status);
}

static int	close_pipes(int	pipes[2][2], int i, bool last)
{
	if (i == 0)
		close_pipe_end(pipes[0][1]);
	else if (last)
		close_pipe_end(pipes[(i + 1) % 2][0]);
	else if (i % 2 == 1)
	{
		close_pipe_end(pipes[0][0]);
		close_pipe_end(pipes[1][1]);
	}
	else if (i % 2 == 0)
	{
		close_pipe_end(pipes[1][0]);
		close_pipe_end(pipes[0][1]);
	}
	else if (i == -1)
	{
		close_pipe_end(pipes[0][0]);
		close_pipe_end(pipes[0][1]);
		close_pipe_end(pipes[1][0]);
		close_pipe_end(pipes[1][1]);
	}
	return (0);
}

static void	child_set_pipes(int fd[2], int pipes[2][2], int i, bool last)
{
	if (i == 0)
	{
		fd[0] = STDIN_FILENO;
		fd[1] = pipes[0][1];
	}
	else if (last)
	{
		fd[0] = pipes[(i + 1) % 2][0];
		fd[1] = STDOUT_FILENO;
	}
	else if (i % 2 == 1)
	{
		fd[0] = pipes[0][0];
		fd[1] = pipes[1][1];
	}
	else if (i % 2 == 0)
	{
		fd[0] = pipes[1][0];
		fd[1] = pipes[0][1];
	}
}

static void	pipes_init(int pipes[2][2])
{
	pipes[0][0] = -1;
	pipes[0][1] = -1;
	pipes[1][0] = -1;
	pipes[1][1] = -1;
}

static int	close_pipe_end(int pipe_end)
{
	if (pipe_end == -1)
		return (0);
	return (close(pipe_end));
}

static char	**list_to_split(t_list *l_token)
{
	int		i;
	char	*tmp;
	char	**split;
	t_list	*iter;

	i = 0;
	iter = l_token;
	while (iter)
	{
		if (!(token_content(iter)->flags & TOK_CONNECTED))
			i++;
		iter = iter->next;
	}
	split = malloc((i + 1) * sizeof(char *));
	i = 0;
	iter = l_token;
	while (iter)
	{
		if (token_content(iter)->flags & TOK_CONNECTED)
		{
			split[i] = ft_strdup(token_content(iter)->string);
			while (token_content(iter)->flags & TOK_CONNECTED)
			{
				tmp = split[i];
				split[i] = ft_strjoin(split[i], token_content(iter->next)->string);
				free(tmp);
				iter = iter->next;
			}
		}
		else
			split[i] = ft_strdup(token_content(iter)->string);
		iter = iter->next;
		i++;
	}
	split[i] = NULL;
	return (split);
}
