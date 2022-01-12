#include "exec.h"
#include "cmd.h"
#include "builtin.h"
#include "signals.h"
#include "env.h"
#include "expand.h"

int	exec_scmd(t_list *scmd, t_list *l_free)
{
	int			pid;
	int			status;
	char		**argv;
	t_list		*l_redir_undo;

	if (exec_scmd_preperation(scmd, &argv) == ERROR)
		return (ERROR);
	if (!(scmd_content(scmd)->l_argv) && scmd_content(scmd)->l_redir)
	{
		status = redir(scmd_content(scmd)->l_redir, &l_redir_undo);
		if (redir_undo(&l_redir_undo) == ERROR)
			status = ERROR;
		return (status);
	}
	if (builtin_check(argv))
	{
		status = redir(scmd_content(scmd)->l_redir, &l_redir_undo);
		if (status != ERROR)
			status = builtin_exec(argv, l_free);
		if (redir_undo(&l_redir_undo) == ERROR)
			status = ERROR;
		ft_free_split(&argv);
		return (status);
	}
	pid = fork();
	if (pid == 0)
	{
		if (redir(scmd_content(scmd)->l_redir, NULL) == ERROR)
			exec_scmd_exit(EXIT_FAILURE, argv);
		status = exec_scmd_exec(argv);
		// if (redir_undo(&l_redir_undo) == ERROR) // geht so nicht, da nur im error case undo wird.....
		// 	status = ERROR;
		exec_scmd_exit(status, argv);
	}
	ft_free_split(&argv);
	return (exec_wait_pid(pid));
}

int	exec_scmd_preperation(t_list *scmd, char ***argv)
{
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
	return (0);
}

int	exec_scmd_exec(char **argv)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	termios_change(true);
	errno = 0;
	// if (ft_strncmp(argv[0], ".", 2) == 0)
	// {
	// 	print_error(SHELL_NAME, argv[0], NULL, "filename argument required");
	// 	return (2); // EXIT_FAILURE
	// }
	if (!ft_strchr(argv[0], '/') && env_get_value("PATH") != NULL)
		if (scmd_search_path(argv) == ERROR)
			return (EXEC_NOTFOUND);
	execve(argv[0], argv, g_env);
	print_error(SHELL_NAME, argv[0], NULL, strerror(errno));
	return (EXIT_FAILURE);
}

void	exec_scmd_exit(int status, char **argv)
{
	if (status == EXEC_NOTFOUND)
		print_error(SHELL_NAME, argv[0], NULL, "command not found");
	else if (status && errno)
	{
		if (errno == ENOENT)
			status = EXEC_NOTFOUND;
		else
			status = EXEC_NOEXEC;
	}
	if (argv)
		ft_free_split(&argv);
	if (g_env)
		ft_free_split(&g_env);
	exit(status);
}
