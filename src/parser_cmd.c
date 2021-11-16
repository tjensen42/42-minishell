#include "parser.h"

int	parser_scmd_set(t_c_scmd *c_scmd, t_list **l_token)
{
	t_list	*tmp;

	c_scmd->type = PAR_SCMD;
	while (parser_get_scmd_type(*l_token) == PAR_SCMD)
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
