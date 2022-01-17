#include "exec.h"

static int	*exec_exit_status_pointer(void);

int	exec_exit_status_get(void)
{
	return (*exec_exit_status_pointer());
}

void	exec_exit_status_set(int status)
{
	if (status == ERROR)
		status = EXIT_FAILURE;
	*exec_exit_status_pointer() = status;
}

static int	*exec_exit_status_pointer(void)
{
	static int	last_exit_status = 0;

	return (&last_exit_status);
}
