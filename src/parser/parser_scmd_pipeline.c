#include "parser.h"

static void		scmd_pipeline_set(t_c_cmd *c_pipeline, t_list **l_scmd);

t_list	*parser_scmd_pipelines(t_list *l_scmd)
{
	t_list	*next;
	t_list	*pipeline;
	t_list	*l_pipeline;

	l_pipeline = NULL;
	while (l_scmd != NULL)
	{
		pipeline = cmd_create(scmd_content(l_scmd)->type);
		if (pipeline == NULL)
		{
			ft_lstclear(&l_pipeline, c_scmd_destroy);
			return (NULL);
		}
		if (cmd_content(pipeline)->type == CMD_SCMD)
			scmd_pipeline_set(cmd_content(pipeline), &l_scmd);
		else
		{
			next = l_scmd->next;
			ft_lstdelone(l_scmd, c_token_destroy);
			l_scmd = next;
		}
		ft_lstadd_back(&l_pipeline, pipeline);
	}
	return (l_pipeline);
}

static void	scmd_pipeline_set(t_c_cmd *c_pipeline, t_list **l_scmd)
{
	t_list	*next;

	c_pipeline->type = CMD_PIPELINE;
	next = (*l_scmd)->next;
	ft_lstadd_back(&(c_pipeline->l_element), *l_scmd);
	(*l_scmd)->next = NULL;
	*l_scmd = next;
	while (*l_scmd != NULL && scmd_content(*l_scmd)->type == CMD_PIPE)
	{
		next = (*l_scmd)->next;
		if (scmd_content(next)->type == CMD_SCMD)
		{
			ft_lstdelone(*l_scmd, c_scmd_destroy);
			ft_lstadd_back(&(c_pipeline->l_element), next);
			*l_scmd = next->next;
			next->next = NULL;
		}
		else
			break ;
	}
}
