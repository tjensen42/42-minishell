#include "exec.h"
#include "cmd.h"
#include "builtin.h"
#include "env.h"

static void	exec_pipeline_element(t_list *element, int pipes[2][2], int i, t_list *l_free);
static int	exec_pipeline_scmd(t_list *scmd, t_list *l_free);

int	exec_pipeline(t_list *pipeline, t_list *l_free)
{
	int		i;
	int		pid;
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
			exec_pipeline_element(iter, pipes, i, l_free);
		pipes_close(pipes, i, (iter->next == NULL));
		iter = iter->next;
		i++;
	}
	return (exec_wait_for_all(pid));
}

static void	exec_pipeline_element(t_list *element, int pipes[2][2], int i, t_list *l_free)
{
	int		fd[2];

	pipes_set(fd, pipes, i, (element->next == NULL));
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	pipes_close(pipes, -1, false);
	if (cmd_type(element) == CMD_SCMD)
		exec_pipeline_scmd(element, l_free);
	else if (cmd_type(element) == CMD_GROUP)
		exit(exec_recursive(cmd_content(element)->l_element, l_free));
}

static int	exec_pipeline_scmd(t_list *scmd, t_list *l_free)
{
	int		status;
	char	**argv;

	if (exec_scmd_preperation(scmd, &argv) == ERROR)
		exec_scmd_exit(EXIT_FAILURE, argv, l_free);
	if (redir(scmd_content(scmd)->l_redir, NULL) == ERROR)
		exec_scmd_exit(EXIT_FAILURE, argv, l_free);
	if (builtin_check(argv))
		status = builtin_exec(argv, l_free);
	else
		status = exec_scmd_exec(argv);
	exec_scmd_exit(status, argv, l_free);
	return (0);
}
