#include "parser.h"
#include "minishell.h"
#include "printer.h"
#include "cmd.h"

static int execute_scmd_pipeline(t_list *l_scmd);

// typedef struct s_execute
// {
// 	int		pipe_r;
// 	int		pipe_w;
// 	char	*here_doc;
// 	int		exit_status;
// };

// redirs hoehere prio als pipes
//
// NEXT STEPS:
// 0.	here_doc
// 1.	Recursive Execution
// 	1.2	Expansion (Variable replacement && Wildcard expansion)
// 	1.3	Builtin check
// 	1.4	Path finding
// 2.	ENV-Variable
// 3.	Builtins
// 4.	Signal Handling
//

// ( ( echo 4 ) | ( ( echo 6 ) ) )

int execution_wrapper(t_list *l_cmd)
{
	execution_recursive(l_cmd, (!l_cmd->next && cmd_content(l_cmd)->type == CMD_PIPELINE));
	return (0);
}


// Pipes müssen immer direkt erkannt werden und pipe info muss über Funktionsaufrauf hinaus erhalten bleiben
int	execution_recursive(t_list *l_cmd, bool pipeline)
{
	int pid;

	pid = 0;
	if (cmd_list_type(l_cmd) == CMD_L_SCMD)
	{
		// execute SCMD Pipeline
		execute_scmd_pipeline(l_cmd);
		// wait for all childs
		return (0);
	}
	if (l_cmd->next && pipeline)
	{
		printf("CREATING PIPE...\n");
		// create PIPE
	}
	if (cmd_content(l_cmd)->type == CMD_PIPELINE)
		execution_recursive(cmd_content(l_cmd)->l_element, true);
	else if (cmd_content(l_cmd)->type == CMD_GROUP)
	{
		printf("CREATING SUBSHELL...\n");
		pid = fork();
		if (pid == 0)
		{
			printf("<<< %d\n", getpid());
			execution_wrapper(cmd_content(l_cmd)->l_element);
			printf(">>> %d\n", getpid());
			exit(0);
		}
		// check if PIPE
		// fork
		// if PID=0: execution_recursive(cmd_content(l_cmd)->l_element, false);
	}
	else
	{
		// && || wait for all childs
		// wait(NULL);
		waitpid(pid, NULL, 0);
		printf("WAITING (&& ||) pid: %d...\n", pid);
		pid = 0;
	}
	if (l_cmd->next) // && exit_status
	{
		// if (pipeline)
			// create pipe_r
		execution_recursive(l_cmd->next, pipeline);
		// execution_wrapper(cmd_content(l_cmd->next)->l_element);
	}
	if (pid != 0)
	{
		printf("waiting for: %d\n", pid);
		waitpid(pid, NULL, 0);
		printf("waited for: %d\n", pid);
	}
	//return (exit_status);
	return (0);
}

static int execute_scmd_pipeline(t_list *l_scmd)
{
	printer_scmd_pipeline(l_scmd, true);
	return (0);
}
