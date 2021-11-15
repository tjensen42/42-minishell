#include "minishell.h"
#include "parser.h"


/* 
 *
 *	PIPELINE PG-LIST
 *
*/

int	parser_list_pipeline_pg(t_list **l_pg)
{
	t_list	*start;
	t_list	*before_pipeline;
	t_list	*l_pipeline;

	l_pipeline = NULL;
	start = *l_pg;
	while (start)
	{
		if ((pg_content(start)->type == PAR_GROUP || pg_content(start)->type == PAR_PIPELINE)
			&& (start->next && pg_content(start->next)->type == PAR_PIPE)
			&& (start->next->next && (pg_content(start->next->next)->type == PAR_GROUP || pg_content(start->next->next)->type == PAR_PIPELINE)))
		{
			l_pipeline = parser_list_pipeline_merge(start);
			if (*l_pg == start)
				*l_pg = l_pipeline;
			else
			{
				before_pipeline = *l_pg;
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
	t_c_pg	*c_pg;
	t_list	*tmp;
	t_list	*tmp2;
	t_list	*merged;

	c_pg = malloc(sizeof(t_c_pg));
	if (c_pg == NULL)
		return (NULL);
	c_pg->type = PAR_PIPELINE;
	c_pg->l_element = NULL;
	tmp = start->next;
	ft_lstadd_back(&(c_pg->l_element), start);
	start->next = NULL;
	while (tmp && pg_content(tmp)->type == PAR_PIPE)
	{
		if (tmp->next && (pg_content(tmp->next)->type == PAR_GROUP || pg_content(tmp->next)->type == PAR_PIPELINE))
		{
			tmp2 = tmp->next;
			ft_lstdelone(tmp, parser_c_pg_destroy);
			ft_lstadd_back(&(c_pg->l_element), tmp2);
			tmp = tmp2->next;
			tmp2->next = NULL;
		}
		else if (pg_content(tmp->next)->type == PAR_O_BRACKET)
			break ;
		else
		{
			print_error(ERR_PIPE);
			return (NULL);
		}
	}
	merged = ft_lstnew(c_pg); 
	merged->next = tmp;
	return (merged);
}

void	parser_c_pg_destroy(void *c_pg)
{
	t_list	*tmp;
	t_c_pg	*free_pg;

	free_pg = c_pg;
	if (free_pg)
	{
		tmp = free_pg->l_element;
		while (tmp)
		{
			if (*(int *)(tmp->content) == PAR_SCMD)
			{
				ft_lstclear(&(free_pg->l_element), parser_c_scmd_destroy);
				break ;
			}
			tmp = tmp->next;
		}
		if (free_pg->l_element)
			ft_lstclear(&(free_pg->l_element), parser_c_pg_destroy);
		free(free_pg);
	}
}
