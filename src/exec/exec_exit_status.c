#include "exec.h"

static int	*exit_status_pointer(void);

int	exit_status_get(void)
{
	return (*exit_status_pointer());
}

void	exit_status_set(int status)
{
	if (status == ERROR)
		status = EXIT_FAILURE;
	*exit_status_pointer() = status;
}

static int	*exit_status_pointer(void)
{
	static int	last_exit_status = 0;

	return (&last_exit_status);
}
