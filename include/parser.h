#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdbool.h>

# include "libft.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */
# define ERROR				-1

# define ERR_UNO_BRACKET	"minishell: Syntax error: Unopened brackets"
# define ERR_UNC_BRACKET	"minishell: Syntax error: Unclosed brackets"
# define ERR_REDIR			"minishell: Syntax error: Incomplete redirection"
# define ERR_QUOTE			"minishell: Syntax error: Unclosed quotation mark"

# define TOK_TEXT			0
# define TOK_BIN_OP			1
# define TOK_PIPE			2
# define TOK_BRACKET		3
# define TOK_REDIR			4
# define TOK_REDIR_FILE		5

# define PAR_CMD			10
# define PAR_AND			11
# define PAR_OR				12
# define PAR_PIPE			13
# define PAR_O_BRACKET		14
# define PAR_C_BRACKET		15

# define WHITESPACES		" \t"
# define QUOT_MARKS			"\'\""

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

typedef struct s_token_content
{
	int		type;
	char	*string;
}	t_c_token;

typedef struct s_element_content
{
	int		type;
	char	**cmd;
	char	**redirs;
	char	**files;
}	t_c_element;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// PARSER
t_list		*parser(t_list *l_token);

int			parser_cmd_set(t_c_element *c_element, t_list *l_token);
bool		parser_token_is_cmd(t_list *token);

t_c_element	*parser_c_element_get(t_list *l_token);
void		parser_c_element_destroy(void *c_element);
t_c_element *element_content(t_list *command);

int			parser_get_type(t_list *token);
char		**parser_get_redirs(t_list *l_token, int i_redir);
char		**parser_get_redir_files(t_list *l_token, int i_redir);

void		parser_printer(t_list *l_command);


// LEXER
void		lexer_token_bin_op(char *str, int *i, t_list **l_token);
void		lexer_token_redir(char *str, int *i, t_list **l_token);
void		lexer_token_pipe(char *str, int *i, t_list **l_token);
void		lexer_token_bracket(char *str, int *i, t_list **l_token);
int			lexer_token_text(char *str, int *i, t_list **l_token);

int			lexer_general_len(char *str);
int			lexer_quote_len(char *str);
int			lexer_special_len(char *chr);

t_list 		*lexer_get_token(char *string, int type);
void		lexer_c_token_destroy(void *content);
t_c_token 	*token_content(t_list *token);

void		lexer_printer(t_list *l_token);

#endif