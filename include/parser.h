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
# define ERR_REDIR			"minishell: Syntax error: Invalid redirection"
# define ERR_QUOTE			"minishell: Syntax error: Unclosed quotation mark"

# define TOK_TEXT			1<<1
# define TOK_S_QUOTE		1<<10
# define TOK_D_QUOTE		1<<11
# define TOK_REDIR_FILE		1<<12
# define TOK_CONNECTED		1<<13

# define TOK_BIN_OP			1<<2
# define TOK_PIPE			1<<3
# define TOK_BRACKET		1<<4
# define TOK_REDIR			1<<5


# define PAR_SCMD			10
# define PAR_PIPELINE		16
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
	int		flags;
	char	*string;
}	t_c_token;

typedef struct s_scmd_content
{
	int		type;
	t_list	*l_argv;
	t_list	*l_redir;
}	t_c_scmd;

typedef struct s_pipeline
{
	int		type;
	t_list	*l_scmd;
}	t_pipeline;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// PARSER
t_list		*parser(t_list *l_token);

int			parser_scmd_set(t_c_scmd *c_element, t_list **l_token);
bool		parser_token_is_cmd(t_list *token);

t_c_scmd	*parser_c_scmd_get(t_list **l_token);
void		parser_c_scmd_destroy(void *c_element);
t_c_scmd	*scmd_content(t_list *element);

int			parser_get_scmd_type(t_list *token);
char		**parser_get_redirs(t_list *l_token, int i_redir);
char		**parser_get_redir_files(t_list *l_token, int i_redir);

void		parser_printer_s1(t_list *l_command);


// LEXER
void		lexer_token_bin_op(char *str, int *i, t_list **l_token);
void		lexer_token_redir(char *str, int *i, t_list **l_token);
void		lexer_token_pipe(char *str, int *i, t_list **l_token);
void		lexer_token_bracket(char *str, int *i, t_list **l_token);
int			lexer_token_text(char *str, int *i, t_list **l_token);
int			lexer_token_quote(char *str, int *i, t_list **l_token);

int			lexer_text_len(char *str);
int			lexer_quote_len(char *str);
int			lexer_special_len(char *chr);

t_list 		*lexer_get_token(char *string, int type);
void		lexer_c_token_destroy(void *content);
t_c_token 	*token_content(t_list *token);

void		lexer_printer(t_list *l_token);

#endif