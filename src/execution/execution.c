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

int execution_wrapper(t_list *l_cmd)
{
	execution_recursive(l_cmd, (!l_cmd->next && cmd_content(l_cmd)->type == CMD_PIPELINE));
	return (0);
}


// Pipes müssen immer direkt erkannt werden und pipe info muss über Funktionsaufrauf hinaus erhalten bleiben
int	execution_recursive(t_list *l_cmd, bool pipeline)
{
	int pid;

	pid = 0;
	if (cmd_list_type(l_cmd) == CMD_L_SCMD)
	{
		// execute SCMD Pipeline
		execute_scmd_pipeline(l_cmd);
		// usleep(100000);
		// wait for all childs
		return (0);
	}
	if (l_cmd->next && pipeline)
	{
		printf("CREATING PIPE...\n");
		// create PIPE
	}
	if (cmd_content(l_cmd)->type == CMD_PIPELINE)
		execution_recursive(cmd_content(l_cmd)->l_element, true);
	else if (cmd_content(l_cmd)->type == CMD_GROUP)
	{
		pid = fork();
		if (pid != 0)
			printf("CREATING SUBSHELL... %d\n", pid);
		if (pid == 0)
		{
			printf("<<< %d\n", getpid());
			execution_wrapper(cmd_content(l_cmd)->l_element);
			printf(">>> %d\n", getpid());
			exit(0);
		}
		// check if PIPE
		// fork
		// if PID=0: execution_recursive(cmd_content(l_cmd)->l_element, false);
	}
	if (l_cmd->next) // && exit_status
	{
		if (cmd_content(l_cmd->next)->type & (CMD_AND | CMD_OR))
		{
			waitpid(pid, NULL, 0);
			printer_other(cmd_content(l_cmd->next)->type);
			printf("(waited for: %d)\n", pid);
			pid = 0;
		}
		// if (pipeline)
			// create pipe_r
		execution_recursive(l_cmd->next, pipeline);
		// execution_wrapper(cmd_content(l_cmd->next)->l_element);
	}
	if (pid != 0)
	{
		printf("waiting for: %d\n", pid);
		waitpid(pid, NULL, 0);
		printf("waited for: %d\n", pid);
	}
	//return (exit_status);
	return (0);
}

static int execute_scmd_pipeline(t_list *l_scmd)
{
	int		i;
	int		pid;
	int		status;
	int		fildes[2][2];
	t_list	*iter;

	printer_scmd_pipeline(l_scmd, true);
	iter = l_scmd;
	i = 0;
	while (iter)
	{
		if (iter->next)
			pipe(fildes[i % 2]);
		pid = fork();
		if (pid == 0)
			scmd_preperation(scmd_content(l_scmd), fildes, i, (iter->next == NULL));
		close_pipes(fildes, i, (iter->next == NULL));
		iter = iter->next;
		i++;
	}
	waitpid(pid, &status, 0);
	waitpid(-1, NULL, 0);
	return (0);
}

static int	close_pipes(int	pipes[2][2], int i, bool last)
{
	if (i == 0)
		close(pipes[0][1]);
	else if (last)
		close(pipes[(i + 1) % 2][0]);
	else if (i % 2 == 1)
	{
		close(pipes[0][0]);
		close(pipes[1][1]);
	}
	else if (i % 2 == 0)
	{
		close(pipes[1][0]);
		close(pipes[0][1]);
	}
	else if (i == -1)
	{
		close(pipes[0][0]);
		close(pipes[0][1]);
		close(pipes[1][0]);
		close(pipes[1][1]);
	}
	return (0);
}

static void	child_set_pipes(int fd[2], int pipes[2][2], int i, bool last)
{
	if (i == 0)
	{
		fd[0] = 0;
		fd[1] = pipes[0][1];
	}
	else if (last)
	{
		fd[0] = pipes[(i + 1) % 2][0];
		fd[1] = 1;
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
	close_pipes(pipes, -1, false);
	// Variable expansion
	// Wildcard expansion
	// Redir processing
	// create ARGV split
	argv = list_to_split(c_scmd->l_argv);
	printf("|%s| |%s|\n", argv[0], argv[1]);
	execve(argv[0], argv, g_env);
	print_error("Error execve");
	ft_free_split(&argv);
	return (ERROR);
}

// int	child_execute(int pipe_r, int pipe_w, char *cmd_str)
// {
// 	int			status;
// 	int			fd[2];
// 	char		**cmd;
// 	extern char	**environ;

// 	cmd = pipex_cmd_get(cmd_str, &status);
// 	if (cmd == NULL)
// 		return (status);
// 	dup2(pipe_r, STDIN_FILENO);
// 	close(pipe_r);
// 	dup2(pipe_w, STDOUT_FILENO);
// 	close(pipe_w);
// 	execve(cmd[0], cmd, environ);
// 	print_error("child error");
// 	ft_free_split(cmd);
// 	return (EXIT_FAILURE);
// }

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
