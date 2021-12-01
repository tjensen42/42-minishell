#include "parser.h"
#include "minishell.h"
#include "printer.h"
#include "cmd.h"
#include "builtin.h"

#include <sys/types.h>
#include <sys/wait.h>

static int scmd_preperation(t_c_scmd *c_scmd, int pipes[2][2], int i, bool last);
static void	child_set_pipes(int fd[2], int pipes[2][2], int i, bool last);
static int	close_pipes(int	pipes[2][2], int i, bool last);
static int execute_scmd_pipeline(t_list *l_scmd);
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

// typedef struct s_execute
// {
// 	int		pipe_r;
// 	int		pipe_w;
// 	char	*here_doc;
// 	int		exit_status;
// };

// redirs hoehere prio als pipes
//
// NEXT STEPS:
// 0.	here_doc
// 1.	Recursive Execution
// 	1.2	Expansion (Variable replacement && Wildcard expansion)
// 	1.3	Builtin check
// 	1.4	Path finding
// 2.	ENV-Variable
// 3.	Builtins
// 4.	Signal Handling
//

// ( ( echo 4 ) | ( ( echo 6 ) ) )

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

int execution_wrapper(t_list *l_cmd)
{
	execution_recursive(l_cmd, (!l_cmd->next && cmd_content(l_cmd)->type == CMD_PIPELINE));
	return (0);
}

// Pipes müssen immer direkt erkannt werden und pipe info muss über Funktionsaufrauf hinaus erhalten bleiben
int	execution_recursive(t_list *l_cmd, bool pipeline)
{
	int pid;
	int status;

	pid = 0;
	status = 0;
	if (cmd_list_type(l_cmd) == CMD_L_SCMD)
		return (execute_scmd_pipeline(l_cmd));
	// if (l_cmd->next && pipeline)
	// {
	// 	printf("CREATING PIPE...\n");
	// }
	if (cmd_content(l_cmd)->type == CMD_PIPELINE)
		status = execution_recursive(cmd_content(l_cmd)->l_element, true);
	else if (cmd_content(l_cmd)->type == CMD_GROUP)
	{
		pid = fork();
		// if (pid != 0)
		// 	printf("CREATING SUBSHELL... %d\n", pid);
		if (pid == 0)
		{
			// printf("<<< %d\n", getpid());
			status = execution_recursive(cmd_content(l_cmd)->l_element, false);
			// execution_wrapper(cmd_content(l_cmd)->l_element);
			// printf(">>> %d\n", getpid());
			exit(status);
		}
	}
	if (l_cmd->next) // && exit_status
	{
		// write(1, "112", 3);
		if (pid && cmd_content(l_cmd->next)->type & (CMD_AND | CMD_OR))
		{
			waitpid(pid, &status, 0);
			// while (wait(NULL) >= 0);
			pid = 0;
		}
		// if (pipeline)
			// create pipe_r
		execution_recursive(l_cmd->next, pipeline);
	}
	if (pid != 0)
	{
		// printf("waiting for: %d\n", pid);
		waitpid(pid, &status, 0);
		while (wait(NULL) >= 0);
		// printf("waited for: %d\n", pid);
	}
	// //return (exit_status);
	return (status);
}

static int execute_scmd_pipeline(t_list *l_scmd)
{
	int		i;
	int		pid;
	int		status;
	int		pipes[2][2];
	t_list	*iter;

	pipes_init(pipes);
	printer_scmd_pipeline(l_scmd, true);
	iter = l_scmd;
	i = 0;
	while (iter)
	{
		if (iter->next)
			if (pipe(pipes[i % 2]) < 0)
				perror("");
		pid = fork();
		if (pid == 0)
			scmd_preperation(scmd_content(iter), pipes, i, (iter->next == NULL));
		close_pipes(pipes, i, (iter->next == NULL));
		iter = iter->next;
		i++;
	}
	waitpid(pid, &status, 0);
	while (wait(NULL) >= 0);
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

static int scmd_preperation(t_c_scmd *c_scmd, int pipes[2][2], int i, bool last)
{
	int		fd[2];
	char	**argv;

	child_set_pipes(fd, pipes, i, last);
	// Variable expansion
	// Wildcard expansion
	// Redir processing
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close_pipes(pipes, -1, false);
	// create ARGV split
	argv = list_to_split(c_scmd->l_argv);
	if (pipex_cmd_set_path(argv) != 0)
	{
		write(2, argv[0], ft_strlen(argv[0]));
		print_error(": command not found");
		ft_free_split(&argv);
		exit (127);
	}
	// printf("|%s| |%s|\n", argv[0], argv[1]);
	// printf("|%d| |%d|\n", fd[0], fd[1]);
	execve(argv[0], argv, g_env);
	print_error("Error execve");
	ft_free_split(&argv);
	exit(ERROR);
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




