#include "token.h"

t_c_token	*token_content(t_list *token)
{
	return ((t_c_token *)token->content);
}

bool	token_is_cmd(t_list *token)
{
	if (token == NULL)
		return (false);
	if (token_content(token)->flags & (TOK_TEXT | TOK_REDIR))
		return (true);
	return (false);
}

t_list	*token_create(char *string, int type)
{
	t_c_token	*c_token;
	t_list		*token;

	c_token = malloc(sizeof(t_c_token));
	if (c_token == NULL)
		return (NULL);
	c_token->flags = type;
	c_token->string = string;
	token = ft_lstnew(c_token);
	if (token == NULL)
		return (NULL);
	token->next = NULL;
	return (token);
}

void	c_token_destroy(void *c_token)
{
	free(((t_c_token *)c_token)->string);
	((t_c_token *)c_token)->string = NULL;
	free(c_token);
}

char	*l_token_to_str(t_list *l_token)
{
	char	*tmp;
	char	*str;

	str = ft_strdup(token_content(l_token)->string);
	while (l_token && (token_content(l_token)->flags & TOK_CONNECTED))
	{
		tmp = str;
		str = ft_strjoin(str, token_content(l_token->next)->string);
		free(tmp);
		if (str == NULL)
			return (NULL);
		l_token = l_token->next;
	}
	return (str);
}

char	**l_token_to_split(t_list *l_token)
{
	int		i;
	char	*tmp;
	char	**split;
	t_list	*iter;

	i = 0;
	iter = l_token;
	while (iter)
	{
		if (!(token_content(iter)->flags & TOK_CONNECTED))
			i++;
		iter = iter->next;
	}
	split = malloc((i + 1) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	i = 0;
	iter = l_token;
	while (iter)
	{
		if (token_content(iter)->flags & TOK_CONNECTED)
		{
			split[i] = ft_strdup(token_content(iter)->string);
			if (split[i] == NULL)
			{
				ft_free_split(&split);
				return (NULL);
			}
			while (token_content(iter)->flags & TOK_CONNECTED)
			{
				tmp = split[i];
				split[i] = ft_strjoin(split[i], token_content(iter->next)->string);
				free(tmp);
				if (split[i] == NULL)
				{
					ft_free_split(&split);
					return (NULL);
				}
				iter = iter->next;
			}
		}
		else
		{
			split[i] = ft_strdup(token_content(iter)->string);
			if (split[i] == NULL)
			{
				ft_free_split(&split);
				return (NULL);
			}
		}
		iter = iter->next;
		i++;
	}
	split[i] = NULL;
	return (split);
}
