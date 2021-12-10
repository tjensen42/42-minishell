#include "exec.h"
#include "cmd.h"
#include "builtin.h"
#include "signals.h"
#include "env.h"

int	exec_scmd(t_list *scmd)
{
	int			pid;
	int			status;
	char		**argv;

	if (exec_scmd_preperation(scmd, &argv) == ERROR)
		return (ERROR);
	if (builtin_check(argv))
	{
		status = builtin_exec(argv);
		ft_free_split(&argv);
		return (status);
	}
	pid = fork();
	if (pid == 0)
	{
		status = exec_scmd_exec(argv);
		exec_scmd_exit(status, argv);
	}
	ft_free_split(&argv);
	return (exec_wait_pid(pid));
}

int	exec_scmd_preperation(t_list *scmd, char ***argv)
{
	// Variable expansion
	// Wildcard expansion
	// Redir processing
	*argv = l_token_to_split(scmd_content(scmd)->l_argv);
	if (*argv == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
	return (0);
}

int	exec_scmd_exec(char **argv)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	termios_change(true);
	errno = 0;
	if (!ft_strchr(argv[0], '/') && env_get_value("PATH") != NULL)
		if (scmd_search_path(argv) == ERROR)
			return (EX_NOTFOUND);
	execve(argv[0], argv, g_env);
	print_error(SHELL_NAME, argv[0], NULL, strerror(errno));
	return (EXIT_FAILURE);
}

void	exec_scmd_exit(int status, char **argv)
{
	if (status == EX_NOTFOUND)
		print_error(SHELL_NAME, argv[0], NULL, "command not found");
	else if (status && errno)
	{
		if (errno == ENOENT)
			status = EX_NOTFOUND;
		else
			status = EX_NOEXEC;
	}
	if (argv)
		ft_free_split(&argv);
	if (g_env)
		ft_free_split(&g_env);
	exit(status);
}
