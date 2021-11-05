#include "parser.h"

bool	parser_token_is_cmd(t_list *token)
{
	int	type;

	if (token == NULL)
		return (false);
	type = token_content(token)->type;
	if (type == TOK_TEXT || type == TOK_REDIR || type == TOK_REDIR_FILE)
		return (true);
	return (false);
}
