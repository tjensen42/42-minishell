#include "libft.h"
#include "global.h"

int	print_error(char *s1, char *s2, char *s3, char *message)
{
	if (s1)
		ft_putstr_fd(s1, 2);
	if (s2)
	{
		if (s1)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(s2, 2);
	}
	if (s3)
	{
		if (s1 || s2)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(s3, 2);
	}
	if (message)
	{
		if (s1 || s2 || s3)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(message, 2);
	}
	ft_putchar_fd('\n', 2);
	return (ERROR);
}

int	count_str_array(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
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

int	split_remove_str(char ***split, char *remove_str)
{
	int		i;
	char	**new_split;

	if (!split_contains_str(*split, remove_str))
		return (ERROR);
	new_split = malloc(count_str_array(*split) * sizeof(char *));
	if (new_split == NULL)
		return (ERROR);
	i = 0;
	while ((*split)[i] != remove_str)
	{
		new_split[i] = (*split)[i];
		i++;
	}
	free(remove_str);
	while ((*split)[i + 1])
	{
		new_split[i] = (*split)[i + 1];
		i++;
	}
	new_split[i] = NULL;
	free(*split);
	*split = new_split;
	return (0);
}

int	split_replace_str(char ***split, char *old_str, char *new_str)
{
	int	i;

	if (*split == NULL)
		return (ERROR);
	i = 0;
	while ((*split)[i] && (*split)[i] != old_str)
		i++;
	if ((*split)[i] != old_str)
		return (ERROR);
	free(old_str);
	(*split)[i] = new_str;
	return (0);
}

int	split_contains_str(char **split, char *str)
{
	int	i;

	if (split == NULL || str == NULL)
		return (false);
	i = 0;
	while (split[i] && split[i] != str)
		i++;
	if (split[i] == str)
		return (true);
	return (false);
}
