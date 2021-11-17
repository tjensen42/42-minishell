#include "cmd.h"

t_c_scmd	*scmd_content(t_list *scmd)
{
	return ((t_c_scmd *)scmd->content);
}

t_c_scmd	*c_scmd_get(void)
{
	t_c_scmd	*c_scmd;

	c_scmd = malloc(sizeof(t_c_scmd));
	if (c_scmd == NULL)
		return (NULL);
	c_scmd->type = 0;
	c_scmd->l_argv = NULL;
	c_scmd->l_redir = NULL;
	return (c_scmd);
}

void	c_scmd_set(t_c_scmd *c_scmd, t_list **l_token)
{
	t_list	*tmp;

	c_scmd->type = cmd_type(*l_token);
	if (c_scmd->type == CMD_SCMD)
	{
		while (cmd_type(*l_token) == CMD_SCMD)
		{
			tmp = (*l_token)->next;
			if (token_content(*l_token)->flags & (TOK_REDIR | TOK_REDIR_FILE))
				ft_lstadd_back(&(c_scmd->l_redir), *l_token);
			else
				ft_lstadd_back(&(c_scmd->l_argv), *l_token);
			(*l_token)->next = NULL;
			*l_token = tmp;
		}
	}
	else
	{
		tmp = *l_token;
		*l_token = (*l_token)->next;
		ft_lstdelone(tmp, c_token_destroy);
	}
}

void	c_scmd_destroy(void *c_scmd)
{
	if (((t_c_scmd *)c_scmd)->l_argv)
		ft_lstclear(&(((t_c_scmd *)c_scmd)->l_argv), c_token_destroy);
	if (((t_c_scmd *)c_scmd)->l_redir)
		ft_lstclear(&(((t_c_scmd *)c_scmd)->l_redir), c_token_destroy);
	free(c_scmd);
}
