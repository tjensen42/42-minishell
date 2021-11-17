#include "parser.h"

static t_list	*parser_cmd_group_create(t_list *open);
static void		parser_cmd_group_link(t_list **l_cmd,
					t_list *open_bracket, t_list *group);

int	parser_cmd_group_merge(t_list **l_cmd)
{
	t_list	*iter;
	t_list	*group;
	t_list	*open_bracket;

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
			group = parser_cmd_group_create(open_bracket);
			if (group == NULL)
				return (ERROR);
			parser_cmd_group_link(l_cmd, open_bracket, group);
			group->next = iter;
			return (1);
		}
		iter = iter->next;
	}
	return (0);
}

static t_list	*parser_cmd_group_create(t_list *open)
{
	t_c_cmd	*c_cmd;
	t_list	*tmp;
	t_list	*last;

	c_cmd = malloc(sizeof(t_c_cmd));
	if (c_cmd == NULL)
		return (NULL);
	c_cmd->type = CMD_GROUP;
	c_cmd->l_element = NULL;
	tmp = open->next;
	ft_lstdelone(open, c_cmd_destroy);
	while (cmd_content(tmp)->type != CMD_C_BRACKET)
	{
		last = tmp;
		tmp = tmp->next;
		ft_lstadd_back(&(c_cmd->l_element), last);
		last->next = NULL;
	}
	ft_lstdelone(tmp, c_cmd_destroy);
	return (ft_lstnew(c_cmd));
}

static void	parser_cmd_group_link(t_list **l_cmd,
								t_list *open_bracket, t_list *group)
{
	t_list	*before_group;

	if (*l_cmd == open_bracket)
		*l_cmd = group;
	else
	{
		before_group = *l_cmd;
		while (before_group->next != open_bracket)
			before_group = before_group->next;
		before_group->next = group;
	}
}
