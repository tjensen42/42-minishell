#include "exec.h"
#include "cmd.h"

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
	//builtin check
	pid = 0;
	if (!pipeline)
		pid = fork();
	if (pid == 0 || pipeline)
	{
		if (pipex_cmd_set_path(argv) != 0)
		{
			write(2, argv[0], ft_strlen(argv[0]));
			// print_error(": command not found"); //// new
			ft_free_split(&argv);
			exit(127);
		}
		execve(argv[0], argv, g_env);
		// print_error("Error execve");
		ft_free_split(&argv);
		exit(ERROR);
	}
	waitpid(pid, &status, 0);
	status = WEXITSTATUS(status);
	return (status);
}
