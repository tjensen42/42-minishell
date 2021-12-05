#include "exec.h"
#include "cmd.h"

int	exec_recursive(t_list *l_cmd)
{
	int	pid;
	int	status;

	pid = 0;
	status = 0;
	if (cmd_type(l_cmd) == CMD_SCMD)
		status = exec_scmd(l_cmd);
	else if (cmd_type(l_cmd) == CMD_PIPELINE)
		status = exec_pipeline(l_cmd);
	else if (cmd_type(l_cmd) == CMD_GROUP)
	{
		pid = fork();
		if (pid == 0)
		{
			status = exec_recursive(cmd_content(l_cmd)->l_element);
			ft_lstclear(&l_cmd, c_cmd_destroy); // für Subshells in subshells müsste man den ursprünglichen listen-Anfang haben
			ft_free_split(&g_env);
			exit(status);
		}
		waitpid(pid, &status, 0);
		status = WEXITSTATUS(status);
	}
	if (l_cmd->next)
	{
		l_cmd = l_cmd->next;
		while (((cmd_content(l_cmd)->type & CMD_AND) && status != 0)
				|| ((cmd_content(l_cmd)->type & CMD_OR) && status == 0))
		{
			l_cmd = l_cmd->next->next;
			if (l_cmd == NULL)
				return (status);
		}
		status = exec_recursive(l_cmd->next);
	}
	return (status);
}
