#include "parser.h"
#include "printer.h"

static void	parser_recursive_merge(t_list **l_cmd);

t_list	*parser(t_list *l_token)
{
	t_list	*l_scmd;
	t_list	*l_cmd;

	l_scmd = parser_scmd_tokens(l_token);
	if (l_scmd == NULL)
		return (NULL);
	printer_cmd(l_scmd);
	printer_structure(l_scmd);
	l_cmd = parser_scmd_pipelines(l_scmd);
	if (l_cmd == NULL)
		return (NULL);
	printer_structure(l_cmd);
	parser_recursive_merge(&l_cmd);
	printer_cmd(l_cmd);
	return (l_cmd);
}

static void	parser_recursive_merge(t_list **l_cmd)
{
	int	group;
	int	pipeline;

	group = 1;
	pipeline = 1;
	while (group > 0 || pipeline > 0)
	{
		group = parser_cmd_group_merge(l_cmd);
		if (group > 0)
			printer_structure(*l_cmd);
		pipeline = parser_cmd_pipeline_merge(l_cmd);
		if (pipeline > 0)
			printer_structure(*l_cmd);
	}
}
