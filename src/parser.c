#include "parser.h"
#include "printer.h"

t_list	*parser_list_scmd(t_list *l_token);

t_list	*parser(t_list *l_token)
{
	int		rt_group;
	int		rt_pipeline;
	t_list	*l_scmd;
	t_list	*l_cmd;

	l_scmd = parser_list_scmd(l_token);
	printer_scmd_structure(l_scmd);
	printer_scmd(l_scmd);

	l_cmd = parser_list_pipeline(l_scmd);
	printer_cmd_structure(l_cmd);
	printer_cmd(l_cmd);

	rt_group = 1;
	rt_pipeline = 1;
	while (rt_group || rt_pipeline)
	{
		rt_group = parser_list_group(&l_cmd);
		if (rt_group)
			printer_cmd_structure(l_cmd);
		rt_pipeline = parser_list_pipeline_pg(&l_cmd);
		if (rt_pipeline)
		 	printer_cmd_structure(l_cmd);
	}
	printer_cmd(l_cmd);
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
		c_scmd = c_scmd_get(&l_token);
		if (c_scmd == NULL)
		{
			ft_lstclear(&l_scmd, c_scmd_destroy);
			return (NULL);
		}
		ft_lstadd_back(&l_scmd, ft_lstnew(c_scmd));
	}
	return (l_scmd);
}

/*
 *
 *	PIPELINE SCMD
 *
*/

t_list	*parser_list_pipeline(t_list *l_scmd)
{
	t_c_cmd	*c_pipeline;
	t_list	*l_pipeline;

	l_pipeline = NULL;
	while (l_scmd != NULL)
	{
		c_pipeline = parser_c_pipeline_get(&l_scmd);
		if (c_pipeline == NULL)
		{
			// ft_lstclear(&l_pipeline, c_cmd_destroy);
			return (NULL);
		}
		ft_lstadd_back(&l_pipeline, ft_lstnew(c_pipeline));
	}
	return (l_pipeline);
}

t_c_cmd	*parser_c_pipeline_get(t_list **l_scmd)
{
	int 	status;
	t_c_cmd	*c_pipeline;
	t_list	*tmp;

	c_pipeline = malloc(sizeof(t_c_cmd));
	if (c_pipeline == NULL)
		return (NULL);
	c_pipeline->l_element = NULL;
	if (scmd_content(*l_scmd)->type == CMD_SCMD)
	{
		status = parser_pipeline_set(c_pipeline, l_scmd);
		if (status == ERROR)
		{
//			c_cmd_destroy(c_pipeline);
			/* RESTE DER SCMD-LIST FREEN! */
			return (NULL);
		}
	}
	else
	{
		c_pipeline->type = scmd_content(*l_scmd)->type;
		tmp = *l_scmd;
		*l_scmd = (*l_scmd)->next;
		ft_lstdelone(tmp, c_scmd_destroy);
	}
	return (c_pipeline);
}

int	parser_pipeline_set(t_c_cmd *c_pipeline, t_list **l_scmd)
{
	t_list	*tmp;

	c_pipeline->type = CMD_PIPELINE;
	tmp = (*l_scmd)->next;
	ft_lstadd_back(&(c_pipeline->l_element), *l_scmd);
	(*l_scmd)->next = NULL;
	*l_scmd = tmp;
	while (*l_scmd != NULL && scmd_content(*l_scmd)->type == CMD_PIPE)
	{
		if (scmd_content((*l_scmd)->next)->type == CMD_SCMD)
		{
			tmp = (*l_scmd)->next;
			ft_lstdelone(*l_scmd, c_scmd_destroy);
			ft_lstadd_back(&(c_pipeline->l_element), tmp);
			*l_scmd = tmp->next;
			tmp->next = NULL;
		}
		else
			break ;
	}
	return (0);
}



/*
 *
 *	Groups
 *
*/

int	parser_list_group(t_list **l_pipeline)
{
	t_list	*tmp;
	t_list	*tmp2;
	t_list	*l_group;
	t_list	*open;

	l_group = NULL;
	tmp = *l_pipeline;
	while (tmp)
	{
		if (cmd_content(tmp)->type == CMD_O_BRACKET)
			open = tmp;
		else if (open != NULL && cmd_content(tmp)->type == CMD_PIPE)
			open = NULL;
		else if (open != NULL && cmd_content(tmp)->type == CMD_C_BRACKET)
		{
			tmp2 = tmp->next;
			l_group = parser_list_group_merge(open);
			if (l_group == NULL)
				return (ERROR);
			l_group->next = tmp2;
			if (*l_pipeline == open)
				*l_pipeline = l_group;
			else
			{
				tmp = *l_pipeline;
				while (tmp->next != open)
					tmp = tmp->next;
				tmp->next = l_group;
			}
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

t_list	*parser_list_group_merge(t_list *open)
{
	t_c_cmd	*c_pg;
	t_list	*tmp;
	t_list	*last;

	c_pg = malloc(sizeof(t_c_cmd));
	if (c_pg == NULL)
		return (NULL);
	c_pg->type = CMD_GROUP;
	c_pg->l_element = NULL;
	tmp = open->next;
	ft_lstdelone(open, c_cmd_destroy);
	while (cmd_content(tmp)->type != CMD_C_BRACKET)
	{
		last = tmp;
		tmp = tmp->next;
		ft_lstadd_back(&(c_pg->l_element), last);
		last->next = NULL;
	}
	ft_lstdelone(tmp, c_cmd_destroy);
	return (ft_lstnew(c_pg));
}

int	parser_get_list_type(t_list *lst)
{
	while (lst)
	{
		if (*(int *)(lst->content) == CMD_SCMD)
			return (CMD_L_SCMD);
		else if (*(int *)(lst->content) == CMD_PIPELINE || *(int *)(lst->content) == CMD_GROUP)
			return (CMD_L_CMD);
		lst = lst->next;
	}
	return (ERROR);
}
