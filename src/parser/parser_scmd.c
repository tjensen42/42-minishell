#include "parser.h"

static t_c_cmd	*parser_c_pipeline_get(t_list **l_scmd);
static void		parser_pipeline_set(t_c_cmd *c_pipeline, t_list **l_scmd);

t_list	*parser_scmd(t_list *l_token)
{
	t_c_scmd	*c_scmd;
	t_list		*l_scmd;

	l_scmd = NULL;
	while (l_token != NULL)
	{
		c_scmd = c_scmd_get();
		if (c_scmd == NULL)
		{
			ft_lstclear(&l_scmd, c_scmd_destroy);
			return (NULL);
		}
		c_scmd_set(c_scmd, &l_token);
		ft_lstadd_back(&l_scmd, ft_lstnew(c_scmd));
	}
	return (l_scmd);
}

t_list	*parser_scmd_pipeline(t_list *l_scmd)
{
	t_c_cmd	*c_pipeline;
	t_list	*l_pipeline;

	l_pipeline = NULL;
	while (l_scmd != NULL)
	{
		c_pipeline = parser_c_pipeline_get(&l_scmd);
		if (c_pipeline == NULL)
		{
			ft_lstclear(&l_pipeline, c_cmd_destroy);
			return (NULL);
		}
		ft_lstadd_back(&l_pipeline, ft_lstnew(c_pipeline));
	}
	return (l_pipeline);
}

static t_c_cmd	*parser_c_pipeline_get(t_list **l_scmd)
{
	t_c_cmd	*c_pipeline;
	t_list	*tmp;

	c_pipeline = malloc(sizeof(t_c_cmd));
	if (c_pipeline == NULL)
		return (NULL);
	c_pipeline->l_element = NULL;
	if (scmd_content(*l_scmd)->type == CMD_SCMD)
		parser_pipeline_set(c_pipeline, l_scmd);
	else
	{
		c_pipeline->type = scmd_content(*l_scmd)->type;
		tmp = *l_scmd;
		*l_scmd = (*l_scmd)->next;
		ft_lstdelone(tmp, c_scmd_destroy);
	}
	return (c_pipeline);
}

static void	parser_pipeline_set(t_c_cmd *c_pipeline, t_list **l_scmd)
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
}
