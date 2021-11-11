#include "parser.h"

t_c_scmd	*parser_c_scmd_get(t_list **l_token)
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
	type = parser_get_scmd_type(*l_token);
	if (type == PAR_SCMD)
	{
		status = parser_scmd_set(c_scmd, l_token);
		if (status == ERROR)
		{
			parser_c_scmd_destroy(c_scmd);
			return (NULL);
		}
	}
	else
	{
		c_scmd->type = type;
		tmp = *l_token;
		*l_token = (*l_token)->next;
		ft_lstdelone(tmp, lexer_c_token_destroy);
	}
	return (c_scmd);
}

void	parser_c_scmd_destroy(void *c_scmd)
{
	if (c_scmd)
	{
		ft_lstclear(&(((t_c_scmd *)c_scmd)->l_argv), lexer_c_token_destroy);
		ft_lstclear(&(((t_c_scmd *)c_scmd)->l_argv), lexer_c_token_destroy);
		free(c_scmd);
	}
}

t_c_scmd *scmd_content(t_list *scmd)
{
	return ((t_c_scmd *)scmd->content);
}
