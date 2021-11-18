#include "parser.h"
#include "printer.h"

static void	parser_pg(t_list **l_cmd);

t_list	*parser(t_list *l_token)
{
	t_list	*l_scmd;
	t_list	*l_cmd;

	l_scmd = parser_scmd(l_token);
	if (l_scmd == NULL)
		return (NULL);
	printer_scmd_structure(l_scmd);
	printer_scmd(l_scmd);
	l_cmd = parser_scmd_pipeline(l_scmd);
	if (l_cmd == NULL)
		return (NULL);
	printer_cmd_structure(l_cmd);
	printer_cmd(l_cmd);
	parser_pg(&l_cmd);
	printer_cmd(l_cmd);
	return (l_cmd);
}

static void	parser_pg(t_list **l_cmd)
{
	// int	i;
	// int	j;
	int	group;
	int	pipeline;

	group = 1;
	pipeline = 1;
	while (group > 0 || pipeline > 0)
	{
		group = parser_cmd_group_merge(l_cmd);
		if (group > 0)
			printer_cmd_structure(*l_cmd);
		pipeline = parser_cmd_pipeline_merge(l_cmd);
		if (pipeline > 0)
			printer_cmd_structure(*l_cmd);
	}

	// i = 1;
	// j = 1;
	// while (i || j)
	// {
	// 	i = 0;
	// 	group = 1;
	// 	while (group)
	// 	{
	// 		group = parser_cmd_group_merge(l_cmd);
	// 		if (group)
	// 		{
	// 			printer_cmd_structure(*l_cmd);
	// 			i++;
	// 		}
	// 	}
	// 	j = 0;
	// 	pipeline = 1;
	// 	while (pipeline)
	// 	{
	// 		pipeline = parser_cmd_pipeline_merge(l_cmd);
	// 		if (pipeline)
	// 		{
	// 			printer_cmd_structure(*l_cmd);
	// 			j++;
	// 		}
	// 	}
	// }
}
