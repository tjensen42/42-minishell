#include "libft.h"
#include "global.h"

int	print_error(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	return (ERROR);
}

int	count_str_array(char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
		i++;
	return (i);
}

int	lst_node_remove(t_list **lst, t_list *node, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst || !(*lst) || !node)
		return (ERROR);
	if (node == *lst)
		*lst = node->next;
	else
	{
		tmp = *lst;
		while (tmp->next && tmp->next != node)
			tmp = tmp->next;
		if (tmp->next != node)
			return (ERROR);
		tmp->next = node->next;
	}
	ft_lstdelone(node, del);
	return (0);
}

t_list	*lst_node_prev(t_list *lst, t_list *node)
{
	if (lst == node)
		return (node);
	while (lst->next && lst->next != node)
		lst = lst->next;
	if (lst->next != node)
		return (NULL);
	return (lst);
}

int	lst_relink(t_list **lst, t_list *node, t_list *start, t_list *end)
{
	t_list	*prev;

	prev = lst_node_prev(*lst, start);
	if (prev == NULL)
		return (ERROR);
	if (start == *lst)
		*lst = node;
	else
		prev->next = node;
	if (end == NULL)
		node->next = NULL;
	else
		node->next = end->next;
	return (0);
}

int	split_append_str(char ***split, char *str)
{
	int		i;
	char	**new_split;

	new_split = malloc((count_str_array(*split) + 2) * sizeof(char *));
	if (new_split == NULL)
		return (ERROR);
	i = 0;
	while ((*split)[i])
	{
		new_split[i] = (*split)[i];
		i++;
	}
	new_split[i] = str;
	new_split[i + 1] = NULL;
	free(*split);
	*split = new_split;
	return (0);
}

int	split_replace_str_i(char ***split, int i, char *new)
{
	if (*split == NULL)
		return (ERROR);
	free((*split)[i]);
	(*split)[i] = new;
	return (0);
}
