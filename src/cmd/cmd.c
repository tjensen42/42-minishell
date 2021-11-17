#include "cmd.h"

t_c_cmd *cmd_content(t_list *pg)
{
	return ((t_c_cmd *)pg->content);
}

int	cmd_type_get(t_list *token)
{
	if (token == NULL)
		return (ERROR);
	else if (token_content(token)->flags & (TOK_TEXT | TOK_REDIR))
		return (CMD_SCMD);
	else if (token_content(token)->flags & TOK_BIN_OP)
	{
		if (token_content(token)->string[0] == '&')
			return (CMD_AND);
		else if (token_content(token)->string[0] == '|')
			return (CMD_OR);
	}
	else if (token_content(token)->flags & TOK_PIPE)
		return (CMD_PIPE);
	else if (token_content(token)->flags & TOK_O_BRACKET)
		return (CMD_O_BRACKET);
	else if (token_content(token)->flags & TOK_C_BRACKET)
		return (CMD_C_BRACKET);
	return (ERROR);
}

void	c_cmd_destroy(void *c_pg)
{
	t_list	*tmp;
	t_c_cmd	*free_pg;

	free_pg = c_pg;
	if (free_pg)
	{
		tmp = free_pg->l_element;
		while (tmp)
		{
			if (*(int *)(tmp->content) == CMD_SCMD)
			{
				ft_lstclear(&(free_pg->l_element), c_scmd_destroy);
				break ;
			}
			tmp = tmp->next;
		}
		if (free_pg->l_element)
			ft_lstclear(&(free_pg->l_element), c_cmd_destroy);
		free(free_pg);
	}
}
