/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:37:06 by hepple            #+#    #+#             */
/*   Updated: 2022/01/17 15:59:26 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "lexer.h"

static int	var_get_splitted(t_list **l_splitted, t_list *token);
static char	*var_needs_splitting(t_list *token);
static void	var_replace_whitespaces(char *str);
static void	var_token_replace(t_list **l_token, t_list *old, t_list *new);

int	expand_var_splitting(t_list **l_token)
{
	t_list	*l_splitted;
	t_list	*iter;
	t_list	*tmp;

	iter = *l_token;
	while (iter)
	{
		tmp = iter->next;
		if (var_needs_splitting(iter) != NULL)
		{
			l_splitted = NULL;
			if (var_get_splitted(&l_splitted, iter) == ERROR)
				return (ERROR);
			if (token_content(iter)->str[0] == VAR_SPACE)
				token_content(
					lst_node_prev(*l_token, iter))->flags &= ~TOK_CONNECTED;
			if (l_splitted != NULL)
				var_token_replace(l_token, iter, l_splitted);
			else
				lst_node_remove(l_token, iter, c_token_destroy);
		}
		iter = tmp;
	}
	return (0);
}

static int	var_get_splitted(t_list **l_splitted, t_list *token)
{
	t_list	*new_token;
	char	**split;
	int		i;

	var_replace_whitespaces(token_content(token)->str);
	split = ft_split(token_content(token)->str, VAR_SPACE);
	if (split == NULL)
		return (ERROR);
	i = 0;
	while (split[i])
	{
		new_token = token_create(split[i],
				token_content(token)->flags & ~TOK_CONNECTED);
		if (new_token == NULL)
			ft_free_split(&split);
		if (new_token == NULL)
			return (ERROR);
		ft_lstadd_back(l_splitted, new_token);
		i++;
	}
	free(split);
	if ((token_content(token)->flags & TOK_CONNECTED)
		&& str_last_chr(token_content(token)->str) != VAR_SPACE)
		token_content(ft_lstlast(*l_splitted))->flags |= TOK_CONNECTED;
	return (0);
}

static char	*var_needs_splitting(t_list *token)
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

static void	var_replace_whitespaces(char *str)
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

static void	var_token_replace(t_list **l_token, t_list *old, t_list *new)
{
	if (old == *l_token)
		*l_token = new;
	else
		lst_node_prev(*l_token, old)->next = new;
	ft_lstlast(new)->next = old->next;
	ft_lstdelone(old, c_token_destroy);
}
