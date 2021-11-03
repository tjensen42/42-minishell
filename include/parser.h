#ifndef PARSER_H
# define PARSER_H

# include "libft.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */
# define ERROR			-1

# define TYPE_GENERAL	0
# define TYPE_SPECIAL	1

# define WHITESPACES	" \t"
# define QUOT_MARKS		"\'\""

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

typedef struct s_token_content
{
	char	*string;
	int		type;
}	t_token_content;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

int		lexer_general_len(char *str);
int		lexer_quote_len(char *str);
int		lexer_special_len(char *chr);

t_list *lexer_get_token(char *string, int type);
void	lexer_destroy_token_content(void *content);

#endif