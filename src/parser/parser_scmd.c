#include "parser.h"

static void	scmd_token_set(t_c_scmd *c_scmd, t_list **l_token);

t_list	*parser_scmd_tokens(t_list *l_token)
{
	t_list	*next;
	t_list	*scmd;
	t_list	*l_scmd;

	l_scmd = NULL;
	while (l_token != NULL)
	{
		scmd = scmd_create(cmd_type(l_token));
		if (scmd == NULL)
		{
			ft_lstclear(&l_scmd, c_scmd_destroy);
			return (NULL);
		}
		if (scmd_content(scmd)->type == CMD_SCMD)
			scmd_token_set(scmd_content(scmd), &l_token);
		else
		{
			next = l_token->next;
			ft_lstdelone(l_token, c_token_destroy);
			l_token = next;
		}
		ft_lstadd_back(&l_scmd, scmd);
	}
	return (l_scmd);
}

static void	scmd_token_set(t_c_scmd *c_scmd, t_list **l_token)
{
	t_list	*next;

	while (cmd_type(*l_token) == CMD_SCMD)
	{
		next = (*l_token)->next;
		if (token_content(*l_token)->flags & (TOK_REDIR | TOK_REDIR_FILE))
			ft_lstadd_back(&(c_scmd->l_redir), *l_token);
		else
			ft_lstadd_back(&(c_scmd->l_argv), *l_token);
		(*l_token)->next = NULL;
		*l_token = next;
	}
}
