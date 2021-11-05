#include "minishell.h"
#include "parser.h"

t_list	*parser(t_list *l_token)
{
	t_list		*l_parse;
	t_c_element	*c_element;

	l_parse = NULL;
	while (l_token != NULL)
	{
		c_element = parser_c_element_get(l_token);
		if (c_element == NULL)
		{
			ft_lstclear(&l_parse, parser_c_element_destroy);
			return (NULL);
		}
		ft_lstadd_back(&l_parse, ft_lstnew(c_element));
		if (parser_token_is_cmd(l_token))
		{
			while (l_token && parser_token_is_cmd(l_token))
				l_token = l_token->next;
		}
		else
			l_token = l_token->next;
	}
	parser_printer(l_parse);
	return (l_parse);
}
