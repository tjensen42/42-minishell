#include "token.h"

char	**l_token_to_split(t_list *l_token)
{
	int		i;
	char	*tmp;
	char	**split;
	t_list	*iter;

	if (l_token == NULL)
		return (NULL);
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
			split[i] = ft_strdup(token_content(iter)->str);
			if (split[i] == NULL)
			{
				ft_free_split(&split);
				return (NULL);
			}
			while (token_content(iter)->flags & TOK_CONNECTED)
			{
				tmp = split[i];
				split[i] = ft_strjoin(split[i], token_content(iter->next)->str);
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
			split[i] = ft_strdup(token_content(iter)->str);
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
