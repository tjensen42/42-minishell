/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:55:15 by hepple            #+#    #+#             */
/*   Updated: 2022/01/17 15:55:27 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static int	l_token_count_strings(t_list *l_token);
static int	l_token_append_connected(t_list **l_token, char **split_str);

char	**l_token_to_split(t_list *l_token)
{
	t_list	*iter;
	char	**split;
	int		i;

	if (l_token == NULL)
		return (NULL);
	split = malloc((l_token_count_strings(l_token) + 1) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	i = 0;
	iter = l_token;
	while (iter)
	{
		split[i] = ft_strdup(token_content(iter)->str);
		if (split[i] == NULL
			|| l_token_append_connected(&iter, &split[i]) == ERROR)
		{
			ft_free_split(&split);
			return (NULL);
		}
		iter = iter->next;
		i++;
	}
	split[i] = NULL;
	return (split);
}

static int	l_token_count_strings(t_list *l_token)
{
	int	i;

	i = 0;
	while (l_token)
	{
		if (!(token_content(l_token)->flags & TOK_CONNECTED))
			i++;
		l_token = l_token->next;
	}
	return (i);
}

static int	l_token_append_connected(t_list **l_token, char **split_str)
{
	char	*tmp;

	while (token_content(*l_token)->flags & TOK_CONNECTED)
	{
		tmp = *split_str;
		*split_str = ft_strjoin(*split_str,
				token_content((*l_token)->next)->str);
		free(tmp);
		if (*split_str == NULL)
			return (ERROR);
		*l_token = (*l_token)->next;
	}
	return (0);
}
