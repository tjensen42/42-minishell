#include "parser.h"

static t_list	*pipeline_start(t_list *l_cmd);
static t_list	*pipeline_create(void);
static int		pipeline_linking(t_list **l_cmd, t_list *pipeline, t_list *start);
static void		parser_cmd_pipeline_add(t_list **pipeline_lst, t_list *cmd);

int	parser_cmd_pipeline_merge(t_list **l_cmd)
{
	t_list	*pipeline;
	t_list	*start;

	start = pipeline_start(*l_cmd);
	if (start == NULL)
		return (0);
	pipeline = group_create();
	if (pipeline == NULL)
		return (ERROR);
	pipeline_linking(l_cmd, pipeline, start);
	return (1);
}

static t_list	*pipeline_start(t_list *l_cmd)
{
	t_list	*iter;

	iter = l_cmd;
	while (iter)
	{
		if ((cmd_content(iter)->type & (CMD_GROUP | CMD_PIPELINE))
			&& iter->next && cmd_content(iter->next)->type == CMD_PIPE
			&& iter->next->next
			&& (cmd_content(iter->next->next)->type
				& (CMD_GROUP | CMD_PIPELINE)))
		{
			return (iter);
		}
		iter = iter->next;
	}
	return (NULL);
}

static t_list	*pipeline_create(void)
{
	t_c_cmd	*c_cmd;

	c_cmd = malloc(sizeof(t_c_cmd));
	if (c_cmd == NULL)
		return (NULL);
	c_cmd->type = CMD_PIPELINE;
	c_cmd->l_element = NULL;
	return (ft_lstnew(c_cmd));
}

static int pipeline_linking(t_list **l_cmd, t_list *pipeline, t_list *start)
{
	t_list	*tmp;
	t_list	*iter;

	iter = start->next;
	parser_cmd_pipeline_add(&(cmd_content(pipeline)->l_element), start);
	while (iter && cmd_content(iter)->type == CMD_PIPE)
	{
		if (iter->next
			&& (cmd_content(iter->next)->type & (CMD_GROUP | CMD_PIPELINE)))
		{
			tmp = iter->next;
			ft_lstdelone(iter, c_cmd_destroy);
			iter = tmp->next;
			parser_cmd_pipeline_add(&(cmd_content(pipeline)->l_element), tmp);
		}
		else
			break ;
	}
	pipeline->next = iter;
	if (start == *l_cmd)
		*l_cmd = start;
	else
	{
		iter = *l_cmd;
		while (iter->next && iter->next != start)
			iter = tmp->next;
		iter->next = pipeline;
	}
	return (0);
}

static void	parser_cmd_pipeline_add(t_list **pipeline_lst, t_list *cmd)
{
	if (cmd_content(cmd)->type == CMD_PIPELINE
		&& cmd_list_type(cmd_content(cmd)->l_element) != CMD_L_SCMD)
	{
		ft_lstadd_back(pipeline_lst, cmd_content(cmd)->l_element);
		cmd_content(cmd)->l_element = NULL;
		ft_lstdelone(cmd, c_cmd_destroy);
	}
	else
	{
		ft_lstadd_back(pipeline_lst, cmd);
		cmd->next = NULL;
	}
}




// int	parser_cmd_pipeline_merge(t_list **l_cmd)
// {
// 	t_list	*iter;
// 	t_list	*pipeline;

// 	pipeline = NULL;
// 	iter = *l_cmd;
// 	while (iter)
// 	{
// 		if ((cmd_content(iter)->type & (CMD_GROUP | CMD_PIPELINE))
// 			&& iter->next && cmd_content(iter->next)->type == CMD_PIPE
// 			&& iter->next->next
// 			&& (cmd_content(iter->next->next)->type
// 				& (CMD_GROUP | CMD_PIPELINE)))
// 		{
			// pipeline = parser_cmd_pipeline_create(start);
			// if (pipeline == NULL)
			// 	return (ERROR);
			// parser_cmd_pipeline_link(l_cmd, start, pipeline);
// 		}
// 		iter = iter->next;
// 	}
// 	return (0);
// }

// static t_list	*parser_cmd_pipeline_create(t_list *start)
// {
// 	t_c_cmd	*c_cmd;
// 	t_list	*merged;
// 	t_list	*after_pipeline;

// 	c_cmd = malloc(sizeof(t_c_cmd));
// 	if (c_cmd == NULL)
// 		return (NULL);
// 	c_cmd->type = CMD_PIPELINE;
// 	c_cmd->l_element = NULL;
// 	after_pipeline = parser_cmd_pipeline_(start, c_cmd);
// 	merged = ft_lstnew(c_cmd);
// 	if (merged == NULL)
// 		return (NULL);
// 	merged->next = after_pipeline;
// 	return (merged);
// }

// static t_list	*parser_cmd_pipeline_(t_list *start, t_c_cmd *c_cmd)
// {
// 	t_list	*iter;
// 	t_list	*tmp;

// 	iter = start->next;
// 	parser_cmd_pipeline_add(&(c_cmd->l_element), start);
// 	while (iter && cmd_content(iter)->type == CMD_PIPE)
// 	{
// 		if (iter->next
// 			&& (cmd_content(iter->next)->type & (CMD_GROUP | CMD_PIPELINE)))
// 		{
// 			tmp = iter->next;
// 			ft_lstdelone(iter, c_cmd_destroy);
// 			iter = tmp->next;
// 			parser_cmd_pipeline_add(&(c_cmd->l_element), tmp);
// 		}
// 		else
// 			break ;
// 	}
// 	return (iter);
// }



// static void	parser_cmd_pipeline_link(t_list **l_cmd,
// 						t_list *iter, t_list *pipeline)
// {
// 	t_list	*before_pipeline;

// 	if (*l_cmd == iter)
// 		*l_cmd = pipeline;
// 	else
// 	{
// 		before_pipeline = *l_cmd;
// 		while (before_pipeline->next != iter)
// 			before_pipeline = before_pipeline->next;
// 		before_pipeline->next = pipeline;
// 	}
// }
