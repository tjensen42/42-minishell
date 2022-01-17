/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_scmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:33:32 by hepple            #+#    #+#             */
/*   Updated: 2022/01/17 18:30:30 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

#include "exec.h"
#include "builtin.h"
#include "cmd.h"
#include "env.h"
#include "expand.h"
#include "signals.h"

static int	exec_builtin(t_list *scmd, char **argv,
				bool subshell, t_list *l_free);

int	exec_scmd(t_list *scmd, bool subshell, t_list *l_free)
{
	char	**argv;
	int		pid;
	int		status;

	if (exec_scmd_preperation(scmd, &argv) == ERROR)
		return (ERROR);
	if (!(scmd_content(scmd)->l_argv))
		return (0);
	if (builtin_check(argv))
		return (exec_builtin(scmd, argv, subshell, l_free));
	pid = fork();
	if (pid == -1)
		ft_free_split(&argv);
	if (pid == -1)
		return (print_error_errno(SHELL_NAME, NULL, NULL));
	if (pid == 0)
	{
		if (redir(scmd_content(scmd)->l_redir, NULL) == ERROR)
			exec_scmd_free_exit(EXIT_FAILURE, argv, l_free);
		status = exec_scmd_exec(argv);
		exec_scmd_free_exit(status, argv, l_free);
	}
	status = exec_wait_pid(pid, argv[0]);
	ft_free_split(&argv);
	return (status);
}

int	exec_scmd_preperation(t_list *scmd, char ***argv)
{
	t_list	*l_redir_undo;
	int		status;

	status = 0;
	*argv = NULL;
	if (expand_var(scmd_content(scmd)) == ERROR)
		return (ERROR);
	if (expand_wildcard(scmd_content(scmd)) == ERROR)
		return (ERROR);
	if (scmd_content(scmd)->l_argv)
	{
		*argv = l_token_to_split(scmd_content(scmd)->l_argv);
		if (*argv == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
	}
	else if (scmd_content(scmd)->l_redir)
	{
		status = redir(scmd_content(scmd)->l_redir, &l_redir_undo);
		if (redir_undo(&l_redir_undo) == ERROR)
			status = ERROR;
	}
	return (status);
}

int	exec_scmd_exec(char **argv)
{
	int	status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	termios_change(true);
	if (!ft_strchr(argv[0], '/') && env_get_value("PATH") != NULL)
	{
		if (exec_scmd_search_path(argv) == ERROR)
		{
			print_error(SHELL_NAME, argv[0], NULL, "command not found");
			return (EXEC_NOTFOUND);
		}
	}
	execve(argv[0], argv, g_env);
	if (errno == ENOENT)
		status = EXEC_NOTFOUND;
	else
		status = EXEC_NOEXEC;
	print_error_errno(SHELL_NAME, argv[0], NULL);
	return (status);
}

void	exec_scmd_free_exit(int status, char **argv, t_list *l_free)
{
	exec_free_all(argv, l_free);
	exit(status);
}

static int	exec_builtin(t_list *scmd, char **argv,
				bool subshell, t_list *l_free)
{
	t_list	*l_redir_undo;
	int		status;

	if (builtin_check(argv))
	{
		status = redir(scmd_content(scmd)->l_redir, &l_redir_undo);
		if (status != ERROR)
			status = builtin_exec(argv, subshell, l_free);
		if (redir_undo(&l_redir_undo) == ERROR)
			status = ERROR;
		ft_free_split(&argv);
		return (status);
	}
	else
		return (ERROR);
}
