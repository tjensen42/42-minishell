#include "cmd.h"

t_c_cmd	*cmd_content(t_list *cmd)
{
	return ((t_c_cmd *)cmd->content);
}

int	cmd_type(t_list *token)
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

void	c_cmd_destroy(void *c_cmd)
{
	t_c_cmd	*free_c_cmd;

	free_c_cmd = c_cmd;
	if (free_c_cmd->l_element)
	{
		if (cmd_list_type(free_c_cmd->l_element) == CMD_L_SCMD)
			ft_lstclear(&(free_c_cmd->l_element), c_scmd_destroy);
		else
			ft_lstclear(&(free_c_cmd->l_element), c_cmd_destroy);
	}
	free(free_c_cmd);
}

int	cmd_list_type(t_list *lst)
{
	while (lst)
	{
		if (*(int *)(lst->content) == CMD_SCMD)
			return (CMD_L_SCMD);
		else if (*(int *)(lst->content) & (CMD_PIPELINE | CMD_GROUP))
			return (CMD_L_CMD);
		lst = lst->next;
	}
	return (ERROR);
}





// while (tmp)
// {
// 	if (*(int *)(tmp->content) == CMD_SCMD)
// 	{
// 		ft_lstclear(&(free_cmd->l_element), c_scmd_destroy);
// 		break ;
// 	}
// 	tmp = tmp->next;
// }
// if (free_cmd->l_element)
// 	ft_lstclear(&(free_cmd->l_element), c_cmd_destroy);
