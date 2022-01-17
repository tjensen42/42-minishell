/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:31:07 by hepple            #+#    #+#             */
/*   Updated: 2022/01/17 15:31:48 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"
#include "cmd.h"

static int	exec_pipeline_pipe_fork(t_list *iter, int pipes[2][2],
				int i, t_list *l_free);
static void	exec_pipeline_element(t_list *element, int pipes[2][2],
				int i, t_list *l_free);
static void	exec_pipeline_scmd(t_list *scmd, t_list *l_free);

int	exec_pipeline(t_list *pipeline, t_list *l_free)
{
	t_list	*iter;
	int		pipes[2][2];
	int		pid;
	int		i;

	pipes_init(pipes);
	i = 0;
	iter = cmd_content(pipeline)->l_element;
	while (iter)
	{
		pid = exec_pipeline_pipe_fork(iter, pipes, i, l_free);
		if (pid == -1)
		{
			pipes_close(pipes, -1, false);
			print_error_errno(SHELL_NAME, NULL, NULL);
			break ;
		}
		pipes_close(pipes, i, (iter->next == NULL));
		iter = iter->next;
		i++;
	}
	return (exec_wait_for_all(pid));
}

static int	exec_pipeline_pipe_fork(t_list *iter, int pipes[2][2],
				int i, t_list *l_free)
{
	int			pid;

	if (iter->next && pipe(pipes[i % 2]) < 0)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		exec_pipeline_element(iter, pipes, i, l_free);
	return (pid);
}

static void	exec_pipeline_element(t_list *element, int pipes[2][2],
				int i, t_list *l_free)
{
	int	fd[2];
	int	status;

	pipes_set(fd, pipes, i, (element->next == NULL));
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	pipes_close(pipes, -1, false);
	if (cmd_type(element) == CMD_SCMD)
		exec_pipeline_scmd(element, l_free);
	else if (cmd_type(element) == CMD_GROUP)
	{
		status = exec_recursive(cmd_content(element)->l_element, true, l_free);
		exec_free_all(NULL, l_free);
		exit (status);
	}
}

static void	exec_pipeline_scmd(t_list *scmd, t_list *l_free)
{
	char	**argv;
	int		status;

	if (exec_scmd_preperation(scmd, &argv) == ERROR)
		exec_scmd_free_exit(EXIT_FAILURE, argv, l_free);
	if (redir(scmd_content(scmd)->l_redir, NULL) == ERROR)
		exec_scmd_free_exit(EXIT_FAILURE, argv, l_free);
	if (!(scmd_content(scmd)->l_argv))
		exec_scmd_free_exit(EXIT_SUCCESS, argv, l_free);
	if (builtin_check(argv))
		status = builtin_exec(argv, true, l_free);
	else
		status = exec_scmd_exec(argv);
	exec_scmd_free_exit(status, argv, l_free);
}
