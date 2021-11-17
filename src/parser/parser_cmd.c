#include "parser.h"


/*
 *
 *	PIPELINE PG-LIST
 *
*/

int	parser_list_pipeline_pg(t_list **l_cmd)
{
	t_list	*start;
	t_list	*before_pipeline;
	t_list	*l_pipeline;

	l_pipeline = NULL;
	start = *l_cmd;
	while (start)
	{
		if ((cmd_content(start)->type == CMD_GROUP || cmd_content(start)->type == CMD_PIPELINE)
			&& (start->next && cmd_content(start->next)->type == CMD_PIPE)
			&& (start->next->next && (cmd_content(start->next->next)->type == CMD_GROUP || cmd_content(start->next->next)->type == CMD_PIPELINE)))
		{
			l_pipeline = parser_list_pipeline_merge(start);
			if (*l_cmd == start)
				*l_cmd = l_pipeline;
			else
			{
				before_pipeline = *l_cmd;
				while (before_pipeline->next != start)
					before_pipeline = before_pipeline->next;
				before_pipeline->next = l_pipeline;
			}
			return (1);
		}
		start = start->next;
	}
	return (0);
}

t_list	*parser_list_pipeline_merge(t_list *start)
{
	t_c_cmd	*c_pg;
	t_list	*tmp;
	t_list	*tmp2;
	t_list	*merged;

	c_pg = malloc(sizeof(t_c_cmd));
	if (c_pg == NULL)
		return (NULL);
	c_pg->type = CMD_PIPELINE;
	c_pg->l_element = NULL;
	tmp = start->next;
	ft_lstadd_back(&(c_pg->l_element), start);
	start->next = NULL;
	while (tmp && cmd_content(tmp)->type == CMD_PIPE)
	{
		if (tmp->next && (cmd_content(tmp->next)->type == CMD_GROUP || cmd_content(tmp->next)->type == CMD_PIPELINE))
		{
			tmp2 = tmp->next;
			ft_lstdelone(tmp, c_cmd_destroy);
			ft_lstadd_back(&(c_pg->l_element), tmp2);
			tmp = tmp2->next;
			tmp2->next = NULL;
		}
		else
			break ;
	}
	merged = ft_lstnew(c_pg);
	merged->next = tmp;
	return (merged);
}
