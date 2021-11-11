#include "minishell.h"
#include "parser.h"

t_list	*parser_list_scmd(t_list *l_token);

t_list	*parser(t_list *l_token)
{
	t_list	*l_scmd;
	t_list	*l_pipeline;
	// t_list	*l_group;

	l_scmd = parser_list_scmd(l_token);
	parser_printer_l_scmd(l_scmd);
	l_pipeline = parser_list_pipeline(l_scmd);
	parser_printer_l_pipeline(l_pipeline);
	parser_printer_l_pipeline_structure(l_pipeline);

	// l_group = parser_list_group(l_pipeline);

	return (l_scmd);
}

/* 
 *
 *	SCMD
 *
*/

t_list	*parser_list_scmd(t_list *l_token)
{
	t_c_scmd	*c_scmd;
	t_list		*l_scmd;

	l_scmd = NULL;
	while (l_token != NULL)
	{
		c_scmd = parser_c_scmd_get(&l_token);
		if (c_scmd == NULL)
		{
			ft_lstclear(&l_scmd, parser_c_scmd_destroy);
			return (NULL);
		}
		ft_lstadd_back(&l_scmd, ft_lstnew(c_scmd));
	}
	return (l_scmd);
}

/* 
 *
 *	PIPELINE
 *
*/

t_list	*parser_list_pipeline(t_list *l_scmd)
{
	t_c_pg	*c_pipeline;
	t_list	*l_pipeline;

	l_pipeline = NULL;
	while (l_scmd != NULL)
	{
		c_pipeline = parser_c_pipeline_get(&l_scmd);
		if (c_pipeline == NULL)
		{
			// ft_lstclear(&l_pipeline, parser_c_pg_destroy);
			return (NULL);
		}
		ft_lstadd_back(&l_pipeline, ft_lstnew(c_pipeline));
	}
	return (l_pipeline);
}

t_c_pg	*parser_c_pipeline_get(t_list **l_scmd)
{
	int 	status;
	t_c_pg	*c_pipeline;
	t_list	*tmp;

	c_pipeline = malloc(sizeof(t_c_pg));
	if (c_pipeline == NULL)
		return (NULL);
	c_pipeline->l_element = NULL;
	if (scmd_content(*l_scmd)->type == PAR_SCMD)
	{
		status = parser_pipeline_set(c_pipeline, l_scmd);
		if (status == ERROR)
		{
//			parser_c_pg_destroy(c_pipeline);
			/* RESTE DER SCMD-LIST FREEN! */
			return (NULL);
		}
	}
	else
	{
		c_pipeline->type = scmd_content(*l_scmd)->type;
		tmp = *l_scmd;
		*l_scmd = (*l_scmd)->next;
		ft_lstdelone(tmp, parser_c_scmd_destroy);
	}
	return (c_pipeline);
}

int	parser_pipeline_set(t_c_pg *c_pipeline, t_list **l_scmd)
{
	t_list	*tmp;

	c_pipeline->type = PAR_PIPELINE;
	tmp = (*l_scmd)->next;	
	ft_lstadd_back(&(c_pipeline->l_element), *l_scmd);
	(*l_scmd)->next = NULL;
	*l_scmd = tmp;
	while (*l_scmd != NULL && scmd_content(*l_scmd)->type == PAR_PIPE)
	{
		if (scmd_content((*l_scmd)->next)->type == PAR_SCMD)
		{
			tmp = *l_scmd;
			*l_scmd = (*l_scmd)->next;
			ft_lstdelone(tmp, parser_c_scmd_destroy);
			ft_lstadd_back(&(c_pipeline->l_element), *l_scmd);
			tmp = (*l_scmd)->next;
			(*l_scmd)->next = NULL;
			(*l_scmd) = tmp;
		}
		else if (scmd_content((*l_scmd)->next)->type == PAR_O_BRACKET)
			break ;
		else
		{
			print_error(ERR_PIPE);
			return (ERROR);
		}
	}
	return (0);
}

t_c_pg *pg_content(t_list *pg)
{
	return ((t_c_pg *)pg->content);
}


/* 
 *
 *	Groups
 *
*/

// t_list	*parser_list_group(t_list *l_pipeline)
// {
// 	t_c_pg	*c_group;
// 	t_list	*l_group;

// 	l_group = NULL;
// 	// while (l_pipeline != NULL)
// 	// {
// 	// 	if (pg_content(l_pipeline)->type != PAR_O_BRACKET)

// 	// 	c_group = parser_c_group_get(&l_pipeline);
// 	// 	if (c_group == NULL)
// 	// 	{
// 	// 		// ft_lstclear(&l_group, parser_c_pg_destroy);
// 	// 		return (NULL);
// 	// 	}
// 	// 	ft_lstadd_back(&l_group, ft_lstnew(c_group));
// 	// }
// 	while (l_pipeline)
// 	{
// 		if (pg_content(l_pipeline)->type == PAR_O_BRACKET)
// 			open = l_pipeline;
// 		else if (open != NULL && pg_content(l_pipeline)->type == PAR_C_BRACKET)
// 		{
// 			status = parser_group_set(c_group, open);
// 			if (status == ERROR)
// 			{
// 				parser_c_pg_destroy(c_group);
// 				/* RESTE DER SCMD-LIST FREEN! */
// 				return (NULL);
// 			}
// 		}
// 		l_pipeline = l_pipeline->next;
// 	}
// 	return (l_group);
// }

// t_c_pg	*parser_c_group_get(t_list **l_pipeline)
// {
// 	int 	status;
// 	t_c_pg	*c_group;
// 	t_list	*tmp;
// 	t_list	*open;

// 	c_group = malloc(sizeof(t_c_pg));
// 	if (c_group == NULL)
// 		return (NULL);
// 	c_group->l_element = NULL;
// 	open = NULL;

// 	while (*l_pipeline)
// 	{
// 		if (pg_content(*l_pipeline)->type == PAR_O_BRACKET)
// 			open = *l_pipeline;
// 		else if (open != NULL && pg_content(*l_pipeline)->type == PAR_C_BRACKET)
// 		{
// 			status = parser_group_set(c_group, open);
// 			if (status == ERROR)
// 			{
// 				parser_c_pg_destroy(c_group);
// 				/* RESTE DER SCMD-LIST FREEN! */
// 				return (NULL);
// 			}
// 		}
// 		*l_pipeline = (*l_pipeline)->next;
// 	}
// 	else
// 	{
// 		c_group->type = scmd_content(*l_pipeline)->type;
// 		tmp = *l_pipeline;
// 		*l_pipeline = (*l_pipeline)->next;
// 		ft_lstdelone(tmp, parser_c_scmd_destroy);
// 	}
// 	return (c_group);
// }



/* 
 *
 *	MERGE
 *
*/


// int	parser_pg_merge(t_list **l_pg, t_list *start, t_list *end)
// {
// 	t_list	*tmp;
// 	t_list	*tmp2;
// 	t_list	*merged;
// 	t_c_pg	*c_pg;

// 	while ((*l_pg)->next != start)
// 		*l_pg = (*l_pg)->next;
// 	c_pg = malloc(sizeof(t_c_pg));
// 	if (c_pg == NULL)
// 		return (ERROR);
// 	merged = ft_lstnew(c_pg);
// 	(*l_pg)->next = merged;
// 	merged->next = end->next;
// 	c_pg->l_element = start;
// 	end->next = NULL;
// 	tmp = c_pg->l_element;
// 	while (tmp != NULL)
// 	{
// 		if (pg_content(tmp)->type == PAR_O_BRACKET 
// 			|| pg_content(tmp)->type == PAR_C_BRACKET 
// 			|| pg_content(tmp)->type == PAR_PIPE)
// 		{
// 			tmp2 = tmp->next;
// 			ft_lstdelone(tmp, parser_c_pg_destroy);
// 			tmp = tmp2;



			
// 		}
// 		else
// 			tmp = tmp->next;
// 	}
// }

