#include "parser.h"

int	parser_get_scmd_type(t_list *token)
{
	if (token == NULL)
		return (ERROR);
	else if (parser_token_is_cmd(token))
		return (PAR_SCMD);
	else if (token_content(token)->flags & TOK_BIN_OP)
	{
		if (token_content(token)->string[0] == '&')
			return (PAR_AND);
		else if (token_content(token)->string[0] == '|')
			return (PAR_OR);
	}
	else if (token_content(token)->flags & TOK_PIPE)
		return (PAR_PIPE);
	else if (token_content(token)->flags & TOK_BRACKET)
	{
		if (token_content(token)->string[0] == '(')
			return (PAR_O_BRACKET);
		else if (token_content(token)->string[0] == ')')
			return (PAR_C_BRACKET);
	}
	return (ERROR);
}

// char	**parser_get_redirs(t_list *l_token, int i_redir)
// {
// 	int		i;
// 	char	**redirs;

// 	redirs = malloc((i_redir + 1) * sizeof(char *));
// 	if (redirs == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (i < i_redir)
// 	{
// 		if (token_content(l_token)->flags & TOK_REDIR)
// 		{
// 			redirs[i] = ft_strdup(token_content(l_token)->string);
// 			i++;
// 		}
// 		l_token = l_token->next;
// 	}
// 	redirs[i] = NULL;
// 	return (redirs);
// }

// char	**parser_get_redir_files(t_list *l_token, int i_redir)
// {
// 	int		i;
// 	char	**files;

// 	files = malloc((i_redir + 1) * sizeof(char *));
// 	if (files == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (i < i_redir)
// 	{
// 		if (token_content(l_token)->flags & TOK_REDIR_FILE)
// 		{
// 			files[i] = ft_strdup(token_content(l_token)->string);
// 			i++;
// 		}
// 		l_token = l_token->next;
// 	}
// 	files[i] = NULL;
// 	return (files);
// }
