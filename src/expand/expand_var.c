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
static int	expand_var_append(char **exp_str, char *str);
static int	expand_var_append_exit(char **exp_str);
static int	expand_var_expansion(t_c_token *c_token, char **exp_str, int *i);

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
	char	*exp_str;

	if (c_token->str == NULL || (c_token->flags & TOK_S_QUOTE)
		|| !ft_strchr(c_token->str, '$'))
		return (0);
	exp_str = ft_strdup("");
	if (exp_str == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
	i = 0;
	while (c_token->str[i])
	{
		while (c_token->str[i] == '$' && c_token->str[i + 1] == '$')
			i++;
		if (expand_var_expansion(c_token, &exp_str, &i) == ERROR)
		{
			free(exp_str);
			return (ERROR);
		}
		i++;
	}
	free(c_token->str);
	c_token->str = exp_str;
	return (0);
}

static int	expand_var_expansion(t_c_token *c_token, char **exp_str, int *i)
{
	if (c_token->str[*i] == '$' && c_token->str[*i + 1] == '?')
	{
		if (expand_var_append_exit(exp_str) == ERROR)
			return (ERROR);
		(*i)++;
	}
	else if (c_token->str[*i] == '$' && (is_var_char(c_token->str[*i + 1])
			|| (c_token->str[*i + 1] == '\0'
				&& !(c_token->flags & (TOK_S_QUOTE | TOK_D_QUOTE))
				&& c_token->flags & TOK_CONNECTED)))
	{
		if (expand_var_append(exp_str, &(c_token->str[*i])) == ERROR)
			return (ERROR);
		while (is_var_char(c_token->str[*i + 1]))
			(*i)++;
	}
	else
		*exp_str = str_append_chr(*exp_str, c_token->str[*i]);
	if (*exp_str == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
	return (0);
}

static int	expand_var_append_exit(char **exp_str)
{
	char	*exit_str;

	exit_str = ft_itoa(exit_status_get());
	if (exit_str == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
	*exp_str = str_append_str(*exp_str, exit_str);
	if (*exp_str == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
	return (0);
}

static int	expand_var_append(char **exp_str, char *str)
{
	char	*var_name;
	char	*var_value;
	int		i;

	var_name = ft_strdup("");
	if (var_name == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
	i = 1;
	while (is_var_char(str[i]))
	{
		var_name = str_append_chr(var_name, str[i]);
		if (var_name == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		i++;
	}
	var_value = env_get_value(var_name);
	free(var_name);
	if (var_value == NULL)
		var_value = "";
	*exp_str = str_append_str(*exp_str, var_value);
	if (*exp_str == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
	return (0);
}

static char	*expand_var_token_needs_splitting(t_list *token)
{
	int	i;

	if (token && !(token_content(token)->flags
			& (TOK_S_QUOTE | TOK_D_QUOTE | TOK_HEREDOC)))
	{
		i = 0;
		while (token_content(token)->str[i])
		{
			if (ft_strchr(WHITESPACES, token_content(token)->str[i]))
				return (&(token_content(token)->str[i]));
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
			if (expand_var_token_list_split_2(&l_splitted, iter) == ERROR)
				return (ERROR);
			if (token_content(iter)->str[0] == VAR_SPACE)
				token_content(
					lst_node_prev(*l_token, iter))->flags &= ~TOK_CONNECTED;
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
	char	*tmp;
	int		i;

	expand_var_replace_whitespaces(token_content(token)->str);
	split = ft_split(token_content(token)->str, VAR_SPACE);
	if (split == NULL)
		return (ERROR);
	i = 0;
	while (split[i])
	{
		new_token = token_create(ft_strdup(split[i]),
				token_content(token)->flags & ~TOK_CONNECTED);
		ft_lstadd_back(l_splitted, new_token);
		i++;
	}
	ft_free_split(&split);
	if ((token_content(token)->flags & TOK_CONNECTED)
		&& str_last_chr(token_content(token)->str) != VAR_SPACE)
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
