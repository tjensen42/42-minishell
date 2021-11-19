#include "parser.h"

static t_list	*group_create(void);
static t_list	*group_open(t_list *l_cmd);
static t_list	*group_close(t_list *bracket_o);
static void		group_linking(t_list **l_cmd, t_list *group, t_list *open, t_list *close);

int	parser_cmd_group_merge(t_list **l_cmd)
{
	t_list	*group;
	t_list	*bracket_o;
	t_list	*bracket_c;

	bracket_o = group_open(*l_cmd);
	bracket_c = group_close(bracket_o);
	if (!bracket_o || !bracket_c)
		return (0);
	if (cmd_content(bracket_o->next)->type == CMD_GROUP
		&& bracket_o->next->next == bracket_c)
	{
		cmd_node_remove(l_cmd, bracket_o);
		cmd_node_remove(l_cmd, bracket_c);
	}
	else
	{
		group = group_create();
		if (group == NULL)
			return (ERROR);
		group_linking(l_cmd, group, bracket_o, bracket_c);
		ft_lstdelone(bracket_o, c_cmd_destroy);
		ft_lstdelone(bracket_c, c_cmd_destroy);
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

static t_list	*group_create(void)
{
	t_c_cmd	*c_cmd;

	c_cmd = malloc(sizeof(t_c_cmd));
	if (c_cmd == NULL)
		return (NULL);
	c_cmd->type = CMD_GROUP;
	c_cmd->l_element = NULL;
	return (ft_lstnew(c_cmd));
}

static void	group_linking(t_list **l_cmd, t_list *group, t_list *open, t_list *close)
{
	t_list	*tmp;
	t_list	*iter;

	cmd_content(group)->l_element = open->next;
	iter = cmd_content(group)->l_element;
	while (iter->next != close)
		iter = iter->next;
	iter->next = NULL;
	if (open == *l_cmd)
		*l_cmd = group;
	else
	{
		tmp = *l_cmd;
		while (tmp->next != open)
			tmp = tmp->next;
		tmp->next = group;
	}
	group->next = close->next;
}


// int	parser_cmd_group_merge(t_list **l_cmd)
// {
// 	t_list	*iter;
// 	t_list	*bracket_o;

// 	bracket_o = NULL;
// 	iter = *l_cmd;
// 	while (iter)
// 	{
// 		if (cmd_content(iter)->type == CMD_O_BRACKET)
// 			bracket_o = iter;
// 		else if (bracket_o && cmd_content(iter)->type == CMD_PIPE)
// 			bracket_o = NULL;
// 		else if (bracket_o && cmd_content(iter)->type == CMD_C_BRACKET)
// 		{
// 			if (cmd_content(bracket_o->next)->type == CMD_GROUP
// 				&& cmd_content(bracket_o->next->next)->type == CMD_C_BRACKET)
// 			{
// 				printf("GROUP\n");
// 				if (cmd_remove_node(l_cmd, bracket_o) == ERROR)
// 					return (ERROR);
// 				if (cmd_remove_node(l_cmd, iter) == ERROR)
// 					return (ERROR);
// 			}
// 			else
// 			{
// 				printf("MERGE\n");
// 				if (parser_cmd_group_create_and_link(l_cmd, bracket_o) == ERROR)
// 					return (ERROR);
// 			}
// 			return (1);
// 		}
// 		iter = iter->next;
// 	}
// 	return (0);
// }


// static int	parser_cmd_group_delete_and_link(t_list **l_cmd, t_list *bracket_o)
// {
// 	t_list	*tmp;
// 	t_list	*group;

// 	group = bracket_o->next;
// 	ft_lstdelone(bracket_o, c_cmd_destroy);
// 	tmp = group->next;
// 	group->next = group->next->next;
// 	ft_lstdelone(tmp, c_cmd_destroy);
// 	if (parser_cmd_group_link(l_cmd, bracket_o, group) == ERROR)
// 		return (ERROR);
// 	return (0);
// }

// static int	parser_cmd_group_create_and_link(t_list **l_cmd, t_list *open)
// {
// 	t_c_cmd	*c_cmd;
// 	t_list	*tmp;
// 	t_list	*last;

// 	c_cmd = malloc(sizeof(t_c_cmd));
// 	if (c_cmd == NULL)
// 		return (ERROR);
// 	c_cmd->type = CMD_GROUP;
// 	c_cmd->l_element = NULL;
// 	tmp = open->next;
// 	ft_lstdelone(open, c_cmd_destroy);
// 	while (cmd_content(tmp)->type != CMD_C_BRACKET)
// 	{
// 		last = tmp;
// 		tmp = tmp->next;
// 		ft_lstadd_back(&(c_cmd->l_element), last);
// 		last->next = NULL;
// 	}
// 	ft_lstdelone(tmp, c_cmd_destroy);
// 	tmp = *l_cmd;
// 	while (tmp->next && tmp->next != open)
// 		tmp = tmp->next;
// 	if (cmd_node_insert_after(l_cmd, ft_lstnew(c_cmd), tmp) == ERROR)
// 		return (ERROR);
// 	return (0);
// }

// static int	parser_cmd_group_link(t_list **l_cmd,
// 								t_list *bracket_o, t_list *group)
// {
// 	t_list	*before_group;

// 	if (group == NULL)
// 		return (ERROR);
// 	if (*l_cmd == bracket_o)
// 		*l_cmd = group;
// 	else
// 	{
// 		before_group = *l_cmd;
// 		while (before_group->next != bracket_o)
// 			before_group = before_group->next;
// 		before_group->next = group;
// 	}
// 	return (0);
// }
