#include "expand.h"
#include "exec.h"
#include "lexer.h"
#include "env.h"

static int	expand_var_token(t_c_token *c_token);
static int	expand_var_append(char **expanded_str, char *str);

int	expand_var_scmd(t_c_scmd *c_scmd)
{
	t_list	*iter;

	iter = c_scmd->l_argv;
	while (iter)
	{
		if (expand_var_token(token_content(iter)) == ERROR)
			return (ERROR);
		iter = iter->next;
	}
	iter = c_scmd->l_redir;
	while (iter)
	{
		if (expand_var_token(token_content(iter)) == ERROR)
			return (ERROR);
		iter = iter->next;
	}
	// Token Splitting
	// l_token_splitting(c_scmd->l_argv);
	// l_token_splitting(c_scmd->l_argv);
	return (0);
}

// static int	l_token_splitting(t_list *l_token)
// {
// 	int	i;

// 	while (l_token)
// 	{
// 		if (!(token_content(l_token)->flags & (TOK_D_QUOTE | TOK_S_QUOTE)))
// 		{
// 			i = 0;
// 			while (token_content(l_token)->string[i])
// 			{
// 				if (ft_strchr(WHITESPACES, token_content(l_token)->string[i]))
// 				{

// 				}
// 				i++;
// 			}
// 		}
// 		l_token = l_token->next;
// 	}
// }

static int	expand_var_token(t_c_token *c_token)
{
	int		i;
	int		i_tmp;
	char	*tmp;
	char	*expanded_str;

	if (c_token->string == NULL || c_token->flags & TOK_S_QUOTE || !ft_strchr(c_token->string, '$'))
		return (0);
	expanded_str = ft_strdup("");
	if (expanded_str == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
	i = 0;
	while (c_token->string[i])
	{
		while (c_token->string[i] == '$' && c_token->string[i + 1] == '$')
			i++;
		if (c_token->string[i] == '$')
		{
			i_tmp = expand_var_append(&expanded_str, &(c_token->string[i]));
			if (i_tmp == ERROR)
			{
				free(expanded_str);
				return (ERROR);
			}
			i += i_tmp;
		}
		else
		{
			expanded_str = str_append_chr(expanded_str, c_token->string[i]);
			i++;
		}
		if (expanded_str == NULL)
		{
			free(expanded_str);
			return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
		}
	}
	free(c_token->string);
	c_token->string = expanded_str;
	return (0);
}

static int expand_var_append(char **expanded_str, char *str)
{
	int		i;
	int		tmp;
	char	*var_name;
	char	*var_value;

	var_name = ft_strdup("");
	if (var_name == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
	i = 1;
	if (str[i] == '?')
	{
		tmp = exit_status_get();
		var_value = ft_itoa(tmp);
		i++;
	}
	else
	{
		while (str[i] && str[i] != '$' && str[i] != '?' && !ft_strchr(WHITESPACES, str[i]) && !ft_strchr(QUOT_MARKS, str[i]))
		{
			var_name = str_append_chr(var_name, str[i]);
			if (var_name == NULL)
				return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
			i++;
		}
		var_value = env_get_value(var_name);
		if (var_value == NULL)
			var_value = ft_strdup("");
	}
	if (var_value == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
	*expanded_str = str_append_str(*expanded_str, var_value);
	if (*expanded_str == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
	return (i);
}
