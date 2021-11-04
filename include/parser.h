#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include "libft.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */
# define ERROR			-1

# define TYPE_TEXT		0
# define TYPE_BIN_OP	1
# define TYPE_PIPE		2
# define TYPE_BRACKET	3
# define TYPE_REDIR		4

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

typedef struct s_redirections
{
	char	*symbol;
	char	*file;
}	t_redir;

typedef struct s_cmd
{
	char	**cmd;
	t_list	*redir_lst;
}	t_cmd;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

int		lexer_general_len(char *str);
int		lexer_quote_len(char *str);
int		lexer_special_len(char *chr);

t_list *lexer_get_token(char *string, int type);
void	lexer_destroy_token_content(void *content);

#endif