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

// static char **parser_cmd_get(t_list *l_token, int i_text)
// {
// 	int 	i;
// 	char	**cmd;

// 	cmd = malloc((i_text + 1) * sizeof(char *));
// 	if (cmd == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (i < i_text)
// 	{
// 		if (token_content(l_token)->flags & TOK_TEXT)
// 		{
// 			cmd[i] = ft_strdup(token_content(l_token)->string);
// 			if (cmd[i] == NULL)
// 				ft_free_split(&cmd);
// 			if (cmd[i] == NULL)
// 				return (NULL);
// 			i++;
// 		}
// 		l_token = l_token->next;
// 	}
// 	cmd[i] = NULL;
// 	return (cmd);
// }

// static int	parser_cmd_count_redir(t_list *l_token)
// {
// 	int	i;

// 	i = 0;
// 	while (l_token)
// 	{
// 		if (token_content(l_token)->flags & TOK_REDIR)
// 			i++;
// 		else if (parser_token_is_cmd(l_token) == false)
// 			break ;
// 		l_token = l_token->next;
// 	}
// 	return (i);
// }

// static int	parser_cmd_count_text(t_list *l_token)
// {
// 	int	i;

// 	i = 0;
// 	while (l_token)
// 	{
// 		if (token_content(l_token)->flags & TOK_TEXT)
// 			i++;
// 		else if (parser_token_is_cmd(l_token) == false)
// 			break ;
// 		l_token = l_token->next;
// 	}
// 	return (i);
// }
