#include "exec.h"
#include "cmd.h"

int	exec_recursive(t_list *l_cmd)
{
	int	pid;

	pid = 0;
	if (cmd_type(l_cmd) == CMD_SCMD)
		exit_status_set(exec_scmd(l_cmd));
	else if (cmd_type(l_cmd) == CMD_PIPELINE)
		exit_status_set(exec_pipeline(l_cmd));
	else if (cmd_type(l_cmd) == CMD_GROUP)
	{
		pid = fork();
		if (pid == 0)
		{
			exit_status_set(exec_recursive(cmd_content(l_cmd)->l_element));
			ft_lstclear(&l_cmd, c_cmd_destroy); // für Subshells in subshells müsste man den ursprünglichen listen-Anfang haben zum freen
			ft_free_split(&g_env);
			exit(exit_status_get());
		}
		exit_status_set(exec_wait_pid(pid));
	}
	if (l_cmd->next)
	{
		l_cmd = l_cmd->next;
		while (((cmd_content(l_cmd)->type & CMD_AND) && exit_status_get() != 0)
				|| ((cmd_content(l_cmd)->type & CMD_OR) && exit_status_get() == 0))
		{
			l_cmd = l_cmd->next->next;
			if (l_cmd == NULL)
				return (exit_status_get());
		}
		exit_status_set(exec_recursive(l_cmd->next));
	}
	return (exit_status_get());
}
