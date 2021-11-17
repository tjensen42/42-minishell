#include "cmd.h"

static int	scmd_set(t_c_scmd *c_scmd, t_list **l_token);

t_c_scmd *scmd_content(t_list *scmd)
{
	return ((t_c_scmd *)scmd->content);
}

t_c_scmd	*c_scmd_get(t_list **l_token)
{
	int 		type;
	int 		status;
	t_c_scmd	*c_scmd;
	t_list		*tmp;

	c_scmd = malloc(sizeof(t_c_scmd));
	if (c_scmd == NULL)
		return (NULL);
	c_scmd->l_argv = NULL;
	c_scmd->l_redir = NULL;
	type = cmd_type_get(*l_token);
	if (type == CMD_SCMD)
	{
		status = scmd_set(c_scmd, l_token);
		if (status == ERROR)
		{
			c_scmd_destroy(c_scmd);
			return (NULL);
		}
	}
	else
	{
		c_scmd->type = type;
		tmp = *l_token;
		*l_token = (*l_token)->next;
		ft_lstdelone(tmp, c_token_destroy);
	}
	return (c_scmd);
}

static int	scmd_set(t_c_scmd *c_scmd, t_list **l_token)
{
	t_list	*tmp;

	c_scmd->type = CMD_SCMD;
	while (cmd_type_get(*l_token) == CMD_SCMD)
	{
		tmp = (*l_token)->next;
		if ((token_content(*l_token)->flags & TOK_REDIR) || (token_content(*l_token)->flags & TOK_REDIR_FILE))
			ft_lstadd_back(&(c_scmd->l_redir), *l_token);
		else
			ft_lstadd_back(&(c_scmd->l_argv), *l_token);
		(*l_token)->next = NULL;
		*l_token = tmp;
	}
	return (0);
}

void	c_scmd_destroy(void *c_scmd)
{
	if (c_scmd)
	{
		ft_lstclear(&(((t_c_scmd *)c_scmd)->l_argv), c_token_destroy);
		ft_lstclear(&(((t_c_scmd *)c_scmd)->l_argv), c_token_destroy);
		free(c_scmd);
	}
}
