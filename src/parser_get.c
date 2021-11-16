#include "parser.h"

int	parser_get_scmd_type(t_list *token)
{
	if (token == NULL)
		return (ERROR);
	else if (lexer_token_is_cmd(token))
		return (PAR_SCMD);
	else if (token_content(token)->flags & TOK_BIN_OP)
	{
		if (token_content(token)->string[0] == '&')
			return (PAR_AND);
		else if (token_content(token)->string[0] == '|')
			return (PAR_OR);
	}
	else if (token_content(token)->flags & TOK_PIPE)
		return (PAR_PIPE);
	else if (token_content(token)->flags & TOK_O_BRACKET)
		return (PAR_O_BRACKET);
	else if (token_content(token)->flags & TOK_C_BRACKET)
		return (PAR_C_BRACKET);
	return (ERROR);
}
