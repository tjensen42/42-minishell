#include "minishell.h"
#include "parser.h"


/* 
 *
 *	PIPELINE PG-LIST
 *
*/

// int	parser_list_pipeline(t_list **l_pipeline)
// {
// 	t_list	*tmp;
// 	t_list	*tmp2;
// 	t_list	*l_group;
// 	t_list	*open;

// 	l_group = NULL;
// 	tmp = *l_pipeline;
// 	while (tmp)
// 	{
// 		if (tmp->next && pg_content(tmp->next)->type == PAR_PIPE)
// 		{
// 			tmp2 = *l_pipeline;
// 			while (tmp2->next != tmp)
// 				tmp2 = tmp2->next;
// 			l_group = parser_list_pipeline_merge(tmp);
// 			l_group->next = tmp2;
// 			if (*l_pipeline == open)
// 			{
// 				*l_pipeline = l_group;
// 			}
// 			else
// 			{
// 				tmp = *l_pipeline;
// 				while (tmp->next != open)
// 					tmp = tmp->next;
// 				tmp->next = l_group;
// 			}
// 			return (1);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

// t_list	*parser_list_pipeline(t_list *open)
// {
// 	t_c_pg	*c_pg;
// 	t_list	*tmp;
// 	t_list	*last;

// 	c_pg = malloc(sizeof(t_c_pg));
// 	if (c_pg == NULL)
// 		return (NULL);
// 	c_pg->type = PAR_GROUP;
// 	c_pg->l_element = NULL;
// 	tmp = open->next;
// 	//ft_lstdelone(open, parser_c_pg_destroy);
// 	while (pg_content(tmp)->type != PAR_C_BRACKET)
// 	{
// 		last = tmp;
// 		tmp = tmp->next;
// 		ft_lstadd_back(&(c_pg->l_element), last);
// 		last->next = NULL;
// 	}
// 	//ft_lstdelone(tmp, parser_c_pg_destroy);
// 	return (ft_lstnew(c_pg));
// }

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
			if (*(int *)(tmp) == PAR_SCMD)
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
