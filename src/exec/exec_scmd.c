#include "exec.h"
#include "cmd.h"
#include "builtin.h"

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
		if (scmd_set_path(argv) != 0)
		{
			ft_free_split(&argv);
			exit(127);
		}
		execve(argv[0], argv, g_env);
		print_error(SHELL_NAME, argv[0], NULL, strerror(errno));
		ft_free_split(&argv);
		exit(ERROR);
	}
	waitpid(pid, &status, 0);
	status = WEXITSTATUS(status);
	return (status);
}
