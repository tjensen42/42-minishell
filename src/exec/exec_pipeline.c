#include "exec.h"
#include "cmd.h"
#include "builtin.h"

static void	exec_pipeline_element(t_list *element, int pipes[2][2], int i, bool last);

int	exec_pipeline(t_list *pipeline)
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
			return (print_error("Too many open files.", NULL, NULL, NULL)); // close all pipes, free and exit
		pid = fork();
		if (pid < 0)
			return (print_error("FORK fail", NULL, NULL, NULL));
		if (pid == 0)
			exec_pipeline_element(iter, pipes, i, (iter->next == NULL));
		close_pipes(pipes, i, (iter->next == NULL));
		iter = iter->next;
		i++;
	}
	waitpid(pid, &status, 0);
	while (wait(NULL) >= 0);
	return (WEXITSTATUS(status));
}

static void	exec_pipeline_element(t_list *element, int pipes[2][2], int i, bool last)
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
