#include "parser.h"

t_list *lexer_get_token(char *string, int type)
{
	t_token_content	*token_content;

	token_content = malloc(sizeof(t_token_content));
	if (token_content == NULL)
		return (NULL);
	token_content->string = string;
	token_content->type = type;
	return (ft_lstnew(token_content));
}

void	lexer_destroy_token_content(void *content)
{
	free(((t_token_content *)content)->string);
	((t_token_content *)content)->string = NULL;
	free(content);
}
