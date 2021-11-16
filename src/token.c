#include "token.h"

bool	token_is_cmd(t_list *token)
{
	if (token == NULL)
		return (false);
	if (token_content(token)->flags & (TOK_TEXT | TOK_REDIR))
		return (true);
	return (false);
}

t_list *token_get(char *string, int type)
{
	t_c_token	*c_token;

	c_token = malloc(sizeof(t_c_token));
	if (c_token == NULL)
		return (NULL);
	c_token->string = string;
	c_token->flags = type;
	return (ft_lstnew(c_token));
}

void	c_token_destroy(void *c_token)
{
	free(((t_c_token *)c_token)->string);
	((t_c_token *)c_token)->string = NULL;
	free(c_token);
}

t_c_token *token_content(t_list *token)
{
	return ((t_c_token *)token->content);
}
