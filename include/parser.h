#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include "libft.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */
# define ERROR				-1

# define TYPE_TEXT			0
# define TYPE_BIN_OP		1
# define TYPE_PIPE			2
# define TYPE_BRACKET		3
# define TYPE_REDIR			4
# define TYPE_REDIR_FILE	5

# define WHITESPACES		" \t"
# define QUOT_MARKS			"\'\""

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

typedef struct s_token_content
{
	char	*string;
	int		type;
}	t_c_token;

typedef struct s_command_content
{
	char	**cmd;
	char	**redirs;
	char	**files;
}	t_c_command;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

int	lexer_redir_mark_files(t_list *token_lst);

int		lexer_general_len(char *str);
int		lexer_quote_len(char *str);
int		lexer_special_len(char *chr);

t_list *lexer_get_token(char *string, int type);
void	lexer_destroy_token_content(void *content);
t_c_token *token_content(t_list *token);

#endif