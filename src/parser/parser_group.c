#include "parser.h"

static t_list	*group_open(t_list *l_cmd);
static t_list	*group_close(t_list *open);

int	parser_cmd_group_merge(t_list **l_cmd)
{
	t_list	*group;
	t_list	*open;
	t_list	*close;

	open = group_open(*l_cmd);
	close = group_close(open);
	if (!open || !close)
		return (0);
	if (cmd_content(open->next)->type == CMD_GROUP && open->next->next == close)
	{
		lst_node_remove(l_cmd, open, c_cmd_destroy);
		lst_node_remove(l_cmd, close, c_cmd_destroy);
	}
	else
	{
		group = cmd_create(CMD_GROUP);
		if (group == NULL)
			return (ERROR);
		cmd_content(group)->l_element = open->next;
		lst_node_prev(*l_cmd, close)->next = NULL;
		lst_relink(l_cmd, group, open, close);
		ft_lstdelone(open, c_cmd_destroy);
		ft_lstdelone(close, c_cmd_destroy);
	}
	return (1);
}

static t_list	*group_open(t_list *l_cmd)
{
	t_list	*iter;
	t_list	*bracket_o;

	bracket_o = NULL;
	iter = l_cmd;
	while (iter != NULL)
	{
		if (cmd_content(iter)->type == CMD_O_BRACKET)
			bracket_o = iter;
		else if (bracket_o && cmd_content(iter)->type == CMD_PIPE)
			bracket_o = NULL;
		else if (bracket_o && cmd_content(iter)->type == CMD_C_BRACKET)
			return (bracket_o);
		iter = iter->next;
	}
	return (NULL);
}

static t_list	*group_close(t_list *bracket_o)
{
	t_list	*bracket_c;

	bracket_c = bracket_o;
	while (bracket_c && cmd_content(bracket_c)->type != CMD_C_BRACKET)
		bracket_c = bracket_c->next;
	if (bracket_c == bracket_o)
		return (NULL);
	return (bracket_c);
}
