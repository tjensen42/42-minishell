#ifndef TOKEN_H
# define TOKEN_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include <stdbool.h>

# include "libft.h"
# include "global.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

# define TOK_TEXT			0b00000000001
# define TOK_S_QUOTE		0b00000000010
# define TOK_D_QUOTE		0b00000000100
# define TOK_REDIR_FILE		0b00000001000
# define TOK_CONNECTED		0b00000010000
# define TOK_BIN_OP			0b00000100000
# define TOK_PIPE			0b00001000000
# define TOK_O_BRACKET		0b00010000000
# define TOK_C_BRACKET		0b00100000000
# define TOK_REDIR			0b01000000000
# define TOK_HEREDOC		0b10000000000

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

typedef struct s_token_content
{
	int		flags;
	char	*string;
}	t_c_token;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

t_list		*token_create(char *string, int type);
t_c_token	*token_content(t_list *token);
void		c_token_destroy(void *c_token);
bool		token_is_cmd(t_list *token);
char		**l_token_to_split(t_list *l_token);
char		*token_to_str(t_list *l_token);

#endif
