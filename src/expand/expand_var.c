#include "expand.h"
#include "exec.h"
#include "lexer.h"
#include "env.h"

static int	expand_var_token_list(t_list *l_token);
static void	expand_var_replace_whitespaces(char *str);
static int	expand_var_token_list_split(t_list **l_token);
static int	expand_var_token_list_split_2(t_list **l_splitted, t_list *token);
static char	*expand_var_token_needs_splitting(t_list *token);
static int	expand_var_token(t_c_token *c_token);
static int	expand_var_append(char **expanded_str, char *str);

int	expand_var_scmd(t_c_scmd *c_scmd)
{
	int		status;

	status = expand_var_token_list(c_scmd->l_argv);
	if (status != ERROR)
		status = expand_var_token_list(c_scmd->l_redir);
	if (status != ERROR)
		status = expand_var_token_list_split(&(c_scmd->l_argv));
	if (status != ERROR)
		status = expand_var_token_list_split(&(c_scmd->l_redir));
	return (status);
}

static int	expand_var_token_list(t_list *l_token)
{
	t_list	*iter;

	iter = l_token;
	while (iter)
	{
		if (expand_var_token(token_content(iter)) == ERROR)
			return (ERROR);
		iter = iter->next;
	}
	return (0);
}

static int	expand_var_token(t_c_token *c_token)
{
	int		i;
	int		i_tmp;
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
		if ((c_token->string[i] == '$' && c_token->string[i + 1] != '\0' && !ft_strchr(WHITESPACES, c_token->string[i + 1])) ||
			(c_token->string[i] == '$' && c_token->string[i + 1] == '\0' && !(c_token->flags & (TOK_S_QUOTE | TOK_D_QUOTE)) && c_token->flags & TOK_CONNECTED))
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
		free(var_name);
		if (var_value == NULL)
			var_value = ft_strdup(""); // muss freed() werden
	}
	if (var_value == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
	*expanded_str = str_append_str(*expanded_str, var_value);
	if (*expanded_str == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
	return (i);
}

static char	*expand_var_token_needs_splitting(t_list *token)
{
	int	i;

	if (token && !(token_content(token)->flags & (TOK_S_QUOTE | TOK_D_QUOTE | TOK_HEREDOC)))
	{
		i = 0;
		while (token_content(token)->string[i])
		{
			if (ft_strchr(WHITESPACES, token_content(token)->string[i]))
				return (&(token_content(token)->string[i]));
			i++;
		}
	}
	return (NULL);
}

static int	expand_var_token_list_split(t_list **l_token)
{
	t_list	*tmp;
	t_list	*iter;
	t_list	*l_splitted;

	iter = *l_token;
	while (iter)
	{
		tmp = iter->next;
		if (expand_var_token_needs_splitting(iter) != NULL)
		{
			l_splitted = NULL;
			expand_var_token_list_split_2(&l_splitted, iter);
			if (token_content(iter)->string[0] == VAR_SPACE)
				token_content(lst_node_prev(*l_token, iter))->flags &= ~TOK_CONNECTED;
			if (l_splitted != NULL)
				expand_lst_replace(l_token, iter, l_splitted);
			else
				lst_node_remove(l_token, iter, c_token_destroy);
		}
		iter = tmp;
	}
	return (0);
}

static int	expand_var_token_list_split_2(t_list **l_splitted, t_list *token)
{
	t_list	*new_token;
	char	**split;
	int		i;

	expand_var_replace_whitespaces(token_content(token)->string);
	split = ft_split(token_content(token)->string, VAR_SPACE);
	i = 0;
	while (split[i])
	{
		new_token = token_create(ft_strdup(split[i]), token_content(token)->flags & ~TOK_CONNECTED);
		ft_lstadd_back(l_splitted, new_token);
		i++;
	}
	ft_free_split(&split);
	if ((token_content(token)->flags & TOK_CONNECTED) && str_last_chr(token_content(token)->string) != VAR_SPACE)
		token_content(ft_lstlast(*l_splitted))->flags |= TOK_CONNECTED;
	return (0);
}

static void	expand_var_replace_whitespaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(WHITESPACES, str[i]))
			str[i] = VAR_SPACE;
		i++;
	}
}
