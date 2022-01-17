/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:35:04 by hepple            #+#    #+#             */
/*   Updated: 2022/01/17 18:27:48 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/wait.h>

#include "exec.h"

static int	print_error_signaled(int signal, char *name);

int	exec_wait_pid(int last_pid, char *name)
{
	int	status;

	status = 0;
	waitpid(last_pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
			ft_putendl_fd("Quit: 3", STDERR_FILENO);
		else if (WTERMSIG(status) == 2)
			ft_putstr_fd("\n", STDERR_FILENO);
		print_error_signaled(WTERMSIG(status), name);
		status = 128 + WTERMSIG(status);
	}
	else if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

int	exec_wait_for_all(int last_pid)
{
	int	pid;
	int	status;

	status = exec_wait_pid(last_pid, NULL);
	pid = 0;
	while (pid >= 0)
		pid = wait(NULL);
	errno = 0;
	return (status);
}

static int	print_error_signaled(int signal, char *name)
{
	if (signal == SIGABRT)
		print_error(name, NULL, "Abort program", "6");
	else if (signal == SIGBUS)
		print_error(name, NULL, "Bus error", "10");
	else if (signal == SIGSEGV)
		print_error(name, NULL, "Segmentation fault", "11");
	else if (signal == SIGTERM)
		print_error(name, NULL, "Terminated", "15");
	return (signal);
}
