#include "exec.h"

int	exec_wait_pid(int last_pid)
{
	int	status;

	status = 0;
	waitpid(last_pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
			ft_putendl_fd("Quit: 3", 2);
		else if (WTERMSIG(status) == 2)
			ft_putstr_fd("\n", 2);
		status = 128 + WTERMSIG(status);
	}
	else if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

int	exec_wait_for_all(int last_pid)
{
	int	status;

	status = exec_wait_pid(last_pid);
	while (wait(NULL) >= 0);
	return (status);
}
