// #include "expand.h"
// #include "exec.h"

// static int	expand_var_token(t_c_token *c_token);

// int	expand_var_scmd(t_c_scmd *c_scmd)
// {
// 	t_list	*iter;

// 	iter = c_scmd->l_argv;
// 	while (iter)
// 	{
// 		if (expand_var_token(token_content(iter)) == ERROR)
// 			return (ERROR);
// 		iter = iter->next;
// 	}
// 	iter = c_scmd->l_redir;
// 	while (iter)
// 	{
// 		if (expand_var_token(token_content(iter)) == ERROR)
// 			return (ERROR);
// 		iter = iter->next;
// 	}
// 	// Token Splitting
// 	return (0);
// }

// static int	expand_var_token(t_c_token *c_token)
// {
// 	int		i;
// 	char	*expanded_str;

// 	if (c_token->flags & TOK_S_QUOTE || !ft_strchr(c_token->string, '$'))
// 		return (0);
// 	expanded_str = ft_strdup("");
// 	if (expanded_str == NULL)
// 		return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
// 	i = 0;
// 	while (c_token->string[i])
// 	{
// 		while (c_token->string[i] == '$' && c_token->string[i + 1] == '$')
// 			i++;
// 		if (c_token->string[i] == '$')
// 		{
// 			i++;
// 			if (c_token->string[i] == '?')
// 			{
// 				 exit_status_get();
// 			}
// 			else
// 			{

// 			}
// 		}
// 		else
// 		{
// 			count++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }


