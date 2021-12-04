#include "exec.h"
#include "cmd.h"
#include "builtin.h"
#include "env.h"

static void scmd_exit(int status, char **argv);

int	exec_scmd(t_list *scmd)
{
	int			pid;
	int			status;
	char		**argv;
	t_c_scmd	*c_scmd;

	c_scmd = scmd_content(scmd);
	// Variable expansion
	// Wildcard expansion
	// Redir processing
	argv = l_token_to_split(c_scmd->l_argv);
	if (builtin_check(argv))
		return (builtin_exec(argv));
	pid = fork();
	if (pid == 0)
	{
		if (!ft_strchr(argv[0], '/') && env_get_value("PATH") != NULL)
			if (scmd_search_path(argv) == ERROR)
				scmd_exit(127, argv);
		execve(argv[0], argv, g_env);
		print_error(SHELL_NAME, argv[0], NULL, strerror(errno));
		scmd_exit(EXIT_FAILURE, argv);
	}
	waitpid(pid, &status, 0);
	status = WEXITSTATUS(status);
	return (status);
}

static void scmd_exit(int status, char **argv)
{
	if (status == 127)
		print_error(SHELL_NAME, argv[0], NULL, "command not found");
	else if (errno == EACCES || errno == ENOENT || errno == ENOEXEC)
		status = EX_NOEXEC;
	ft_free_split(&argv);
	exit(status);
}
