#include "parser.h"
#include "cmd.h"

//
// NEXT STEPS:
// 1.	Recursive Execution
// 	1.2	Expansion (Variable replacement && Wildcard expansion)
// 	1.3	Builtin check
// 	1.4	Path finding
// 3.	Builtins
// 4.	here_doc
// 5.	Signal Handling
//



// Pipes müssen immer direkt erkannt werden und pipe info muss über Funktionsaufrauf hinaus erhalten bleiben
static void	execution_recursive(t_list *l_cmd, bool pipeline)
{
	if (cmd_list_type(l_cmd) == CMD_L_SCMD)
	{
		// execute SCMD Pipeline
		return ;
	}
	if (cmd_content(l_cmd)->type == CMD_PIPELINE)
		execution_recursive(cmd_content(l_cmd)->l_element, true);
	else if (cmd_content(l_cmd)->type == CMD_GROUP)
	{
		// fork
		// if PID=0: execution_recursive(cmd_content(l_cmd)->l_element, false);
	}
	else
		// wait for all childs
	if (l_cmd->next && exit_status)
	{
		if (pipeline)
			// create pipe
		execution_recursive(l_cmd->next, pipeline);
	}
}
