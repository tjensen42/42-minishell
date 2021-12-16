#include "expand.h"

void	expand_lst_replace(t_list **l_token, t_list *old, t_list *new)
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
	if (prev != old)
		prev->next = new;
	else
		*l_token = new;
}
