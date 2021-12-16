#include "expand.h"

void	expand_lst_replace(t_list **l_token, t_list *old, t_list *new)
{
	if (old == *l_token)
		*l_token = new;
	else
		lst_node_prev(*l_token, old)->next = new;
	ft_lstlast(new)->next = old->next;
	ft_lstdelone(old, c_token_destroy);
}

// Logic schöner?
void	expand_lst_replace_connected(t_list **l_token, t_list *old, t_list *new)
{
	t_list	*tmp;
	t_list	*prev;
	t_list	*iter;

	iter = old;
	prev = lst_node_prev(*l_token, old);
	while (iter && token_content(iter)->flags & TOK_CONNECTED)
	{
		tmp = iter->next;
		lst_node_remove(l_token, iter, c_token_destroy);
		iter = tmp;
	}
	ft_lstlast(new)->next = iter->next;
	lst_node_remove(l_token, iter, c_token_destroy);
	if (prev == old)
		*l_token = new;
	else
		prev->next = new;
}
