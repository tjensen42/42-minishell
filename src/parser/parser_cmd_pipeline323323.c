#include "parser.h"

static t_list	*parser_cmd_pipeline_create(t_list *start);
static void		parser_cmd_pipeline_link(t_list **l_cmd,
					t_list *iter, t_list *pipeline);
static t_list	*parser_cmd_pipeline_(t_list *start, t_c_cmd *c_cmd);
static void		cmd_pipeline_add(t_list **lst, t_list *cmd);

int	parser_cmd_pipeline_merge(t_list **l_cmd)
{
	t_list	*iter;
	t_list	*pipeline;

	pipeline = NULL;
	iter = *l_cmd;
	while (iter)
	{
		if ((cmd_content(iter)->type & (CMD_GROUP | CMD_PIPELINE))
			&& iter->next && cmd_content(iter->next)->type == CMD_PIPE
			&& iter->next->next
			&& (cmd_content(iter->next->next)->type
				& (CMD_GROUP | CMD_PIPELINE)))
		{
			pipeline = parser_cmd_pipeline_create(iter);
			if (pipeline == NULL)
				return (ERROR);
			parser_cmd_pipeline_link(l_cmd, iter, pipeline);
			return (1);
		}
		iter = iter->next;
	}
	return (0);
}

static t_list	*parser_cmd_pipeline_create(t_list *start)
{
	t_c_cmd	*c_cmd;
	t_list	*merged;
	t_list	*after_pipeline;

	c_cmd = malloc(sizeof(t_c_cmd));
	if (c_cmd == NULL)
		return (NULL);
	c_cmd->type = CMD_PIPELINE;
	c_cmd->l_element = NULL;
	after_pipeline = parser_cmd_pipeline_(start, c_cmd);
	merged = ft_lstnew(c_cmd);
	if (merged == NULL)
		return (NULL);
	merged->next = after_pipeline;
	return (merged);
}

static t_list	*parser_cmd_pipeline_(t_list *start, t_c_cmd *c_cmd)
{
	t_list	*iter;
	t_list	*tmp;

	// iter = start->next;
	// ft_lstadd_back(&(c_cmd->l_element), start);
	// start->next = NULL;
	iter = start->next;
	cmd_pipeline_add(&(c_cmd->l_element), start);
	while (iter && cmd_content(iter)->type == CMD_PIPE)
	{
		if (iter->next
			&& (cmd_content(iter->next)->type & (CMD_GROUP | CMD_PIPELINE)))
		{
			tmp = iter->next;
			ft_lstdelone(iter, c_cmd_destroy);
			iter = tmp->next;
			// ft_lstadd_back(&(c_cmd->l_element), tmp);
			// tmp->next = NULL;
			cmd_pipeline_add(&(c_cmd->l_element), tmp);
		}
		else
			break ;
	}
	return (iter);
}

static void	cmd_pipeline_add(t_list **lst, t_list *cmd)
{
	if (cmd_content(cmd)->type == CMD_PIPELINE
		&& cmd_list_type(cmd_content(cmd)->l_element) != CMD_L_SCMD)
	{
		ft_lstadd_back(lst, cmd_content(cmd)->l_element);
		cmd_content(cmd)->l_element = NULL;
		ft_lstdelone(cmd, c_cmd_destroy);
	}
	else
	{
		ft_lstadd_back(lst, cmd);
		cmd->next = NULL;
	}
}

static void	parser_cmd_pipeline_link(t_list **l_cmd,
						t_list *iter, t_list *pipeline)
{
	t_list	*before_pipeline;

	if (*l_cmd == iter)
		*l_cmd = pipeline;
	else
	{
		before_pipeline = *l_cmd;
		while (before_pipeline->next != iter)
			before_pipeline = before_pipeline->next;
		before_pipeline->next = pipeline;
	}
}
