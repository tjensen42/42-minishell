#include "parser.h"

t_list *lexer_get_token(char *string, int type)
{
	t_c_token	*c_token;

	c_token = malloc(sizeof(t_c_token));
	if (c_token == NULL)
		return (NULL);
	c_token->string = string;
	c_token->type = type;
	return (ft_lstnew(c_token));
}

void	lexer_destroy_token_content(void *c_token)
{
	free(((t_c_token *)c_token)->string);
	((t_c_token *)c_token)->string = NULL;
	free(c_token);
}

t_c_token *token_content(t_list *token)
{
	return ((t_c_token *)token->content);
}
