#include "parser.h"

static int	parser_cmd_group_create_and_link(t_list **l_cmd, t_list *start, t_list *open_bracket);
static int		parser_cmd_group_link(t_list **l_cmd,
					t_list *open_bracket, t_list *group);
static int	parser_cmd_group_delete_and_link(t_list **l_cmd, t_list *open_bracket);

int	parser_cmd_group_merge(t_list **l_cmd)
{
	t_list	*iter;
	t_list	*group;
	t_list	*open_bracket;

	open_bracket = NULL;
	group = NULL;
	iter = *l_cmd;
	while (iter)
	{
		if (cmd_content(iter)->type == CMD_O_BRACKET)
			open_bracket = iter;
		else if (open_bracket && cmd_content(iter)->type == CMD_PIPE)
			open_bracket = NULL;
		else if (open_bracket && cmd_content(iter)->type == CMD_C_BRACKET)
		{

			iter = iter->next;
			if (cmd_content(open_bracket->next)->type == CMD_GROUP && cmd_content(open_bracket->next->next)->type == CMD_C_BRACKET)
			{
				if (parser_cmd_group_delete_and_link(l_cmd, open_bracket) == ERROR)
					return (ERROR);
			}
			else
			{
				if (parser_cmd_group_create_and_link(l_cmd, open_bracket, open_bracket) == ERROR)
					return (ERROR);
			}
			group->next = iter;
			return (1);
		}
		iter = iter->next;
	}
	return (0);
}

static int	parser_cmd_group_delete_and_link(t_list **l_cmd, t_list *open_bracket)
{
	t_list	*tmp;
	t_list	*group;

	group = open_bracket->next;
	ft_lstdelone(open_bracket, c_cmd_destroy);
	tmp = group->next;
	group->next = group->next->next;
	ft_lstdelone(tmp, c_cmd_destroy);
	if (parser_cmd_group_link(l_cmd, open_bracket, group) == ERROR)
		return (ERROR);
	return (0);
}

static int	parser_cmd_group_create_and_link(t_list **l_cmd, t_list *start, t_list *open_bracket)
{
	t_c_cmd	*c_cmd;
	t_list	*tmp;
	t_list	*last;

	c_cmd = malloc(sizeof(t_c_cmd));
	if (c_cmd == NULL)
		return (ERROR);
	c_cmd->type = CMD_GROUP;
	c_cmd->l_element = NULL;
	tmp = start->next;
	ft_lstdelone(start, c_cmd_destroy);
	while (cmd_content(tmp)->type != CMD_C_BRACKET)
	{
		last = tmp;
		tmp = tmp->next;
		ft_lstadd_back(&(c_cmd->l_element), last);
		last->next = NULL;
	}
	ft_lstdelone(tmp, c_cmd_destroy);
	if (parser_cmd_group_link(l_cmd, open_bracket, ft_lstnew(c_cmd)) == ERROR)
		return (ERROR);
	return (0);
}

static int	parser_cmd_group_link(t_list **l_cmd,
								t_list *open_bracket, t_list *group)
{
	t_list	*before_group;

	if (group == NULL)
		return (ERROR);
	if (*l_cmd == open_bracket)
		*l_cmd = group;
	else
	{
		before_group = *l_cmd;
		while (before_group->next != open_bracket)
			before_group = before_group->next;
		before_group->next = group;
	}
	return (0);
}
