#ifndef LEXER_H
# define LEXER_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include <stdbool.h>

# include "libft.h"
# include "global.h"
# include "token.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

# define WHITESPACES		" \t\n"
# define QUOT_MARKS			"\'\""

# define ERR_SYNTAX			"syntax error"

# define ERR_UNO_BRACKET	"unopened brackets"
# define ERR_UNC_BRACKET	"unclosed brackets"
# define ERR_EMPTY_BRACKET	"empty brackets"
# define ERR_REDIR			"invalid redirection"
# define ERR_QUOTE			"unclosed quotation mark"
# define ERR_LIST			"incomplete command list"
# define ERR_MISS_OP		"missing operator"
# define ERR_PIPE			"incomplete pipe"

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// LEXER
t_list		*lexer(char *input);

// LEXER_TOKEN_TEXT
int			lexer_token_text(char *str, int *i, t_list **l_token);
int			lexer_token_quote(char *str, int *i, t_list **l_token);

// LEXER_TOKEN_OTHER
int			lexer_token_bin_op(char *str, int *i, t_list **l_token);
int			lexer_token_redir(char *str, int *i, t_list **l_token);
int			lexer_token_pipe(char *str, int *i, t_list **l_token);
int			lexer_token_bracket(char *str, int *i, t_list **l_token);

// TOKEN_UTILS
bool		token_is_cmd(t_list *token);
t_list		*token_create(char *string, int type);
void		c_token_destroy(void *content);
t_c_token	*token_content(t_list *token);

// SYNTAX
int			lexer_syntax_check(t_list *l_token);

// PRINTER
void		printer_token(t_list *l_token);

#endif
