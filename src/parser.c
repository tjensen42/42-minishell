#include "minishell.h"
#include "parser.h"

t_list	*parser(t_list *l_token)
{
	t_list		*l_scmd;
	t_c_scmd	*c_scmd;

	l_scmd = NULL;
	while (l_token != NULL)
	{
		c_scmd = parser_c_scmd_get(&l_token);
		if (c_scmd == NULL)
		{
			ft_lstclear(&l_scmd, parser_c_scmd_destroy);
			return (NULL);
		}
		ft_lstadd_back(&l_scmd, ft_lstnew(c_scmd));
		// if (parser_token_is_cmd(l_token))
		// {
		// 	while (l_token && parser_token_is_cmd(l_token))
		// 		l_token = l_token->next;
		// }
		// else
		// 	l_token = l_token->next;
	}
	parser_printer_s1(l_scmd);
	parser_printer_s1(l_scmd);
	return (l_scmd);
}
