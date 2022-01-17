#include "exec.h"
#include "cmd.h"

#include <readline/readline.h>

static void	exec_group(t_list *l_cmd, t_list *l_free);
static bool	exec_op_check(t_list *l_cmd);

int	exec_recursive(t_list *l_cmd, bool subshell, t_list *l_free)
{
	int	pid;

	if (cmd_type(l_cmd) == CMD_SCMD)
		exit_status_set(exec_scmd(l_cmd, subshell, l_free));
	else if (cmd_type(l_cmd) == CMD_PIPELINE)
		exit_status_set(exec_pipeline(l_cmd, l_free));
	else if (cmd_type(l_cmd) == CMD_GROUP)
	{
		pid = fork();
		if (pid == 0)
			exec_group(l_cmd, l_free);
		if (pid == -1)
			exit_status_set(print_error_errno(SHELL_NAME, NULL, NULL));
		else
			exit_status_set(exec_wait_pid(pid, NULL));
	}
	if (l_cmd->next)
	{
		l_cmd = l_cmd->next;
		while (l_cmd && exec_op_check(l_cmd))
		{
			l_cmd = l_cmd->next->next;
			if (l_cmd == NULL)
				return (exit_status_get());
		}
		exit_status_set(exec_recursive(l_cmd->next, subshell, l_free));
	}
	return (exit_status_get());
}

static void	exec_group(t_list *l_cmd, t_list *l_free)
{
	int	status;

	status = exec_recursive(cmd_content(l_cmd)->l_element, true, l_free);
	exec_free_all(NULL, l_free);
	exit(status);
}

static bool	exec_op_check(t_list *l_cmd)
{
	if (cmd_content(l_cmd)->type & CMD_AND && exit_status_get() != 0)
		return (true);
	else if (cmd_content(l_cmd)->type & CMD_OR && exit_status_get() == 0)
		return (true);
	else
		return (false);
}

void	exec_free_all(char **argv, t_list *l_free)
{
	if (argv)
		ft_free_split(&argv);
	if (l_free)
		ft_lstclear(&l_free, c_cmd_destroy);
	if (g_env)
		ft_free_split(&g_env);
	rl_clear_history();
}
