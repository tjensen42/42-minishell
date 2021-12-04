#include "exec.h"
#include "cmd.h"
#include "builtin.h"

int	execution_scmd(t_list *scmd, bool pipeline)
{
	int			pid;
	int			status;
	char		**argv;
	t_c_scmd	*c_scmd;

	c_scmd = scmd_content(scmd);
	// Variable expansion
	// Wildcard expansion
	// Redir processing
	argv = list_to_split(c_scmd->l_argv);
	if (builtin_check(argv))
	{
		if (pipeline)
			exit(builtin_exec(argv));
		else
			return (builtin_exec(argv));
	}
	//builtin check
	pid = 0;
	if (!pipeline)
		pid = fork();
	if (pid == 0 || pipeline)
	{
		if (pipex_cmd_set_path(argv) != 0)
		{
			print_error(SHELL_NAME, argv[0], NULL, "command not found");
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
