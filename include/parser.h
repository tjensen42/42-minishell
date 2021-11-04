#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdbool.h>

# include "libft.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */
# define ERROR				-1

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

typedef struct s_command_content
{
	int		type;
	char	**cmd;
	char	**redirs;
	char	**files;
}	t_c_command;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

t_c_command *command_content(t_list *command);
int	parser_cmd_count_redir(t_list *l_token);
int	parser_cmd_count_text(t_list *l_token);
bool	parser_token_is_command(t_list *token);
int	parser_get_type(t_list *token);
t_c_command	*parser_get_command(t_list *l_token);
char	**parser_get_redirs(t_list *l_token, int i_redir);
char	**parser_get_redir_files(t_list *l_token, int i_redir);
char **parser_get_cmd(t_list *l_token, int i_text);
int	parser(t_list *l_token);
void	parser_printer(t_list *l_command);

int	lexer_redir_mark_files(t_list *token_lst);

int		lexer_general_len(char *str);
int		lexer_quote_len(char *str);
int		lexer_special_len(char *chr);

t_list *lexer_get_token(char *string, int type);
void	lexer_destroy_token_content(void *content);
t_c_token *token_content(t_list *token);

#endif