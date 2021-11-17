#ifndef CMD_H
# define CMD_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "libft.h"
# include "global.h"
# include "token.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

# define CMD_SCMD			1

# define CMD_AND			2
# define CMD_OR				3
# define CMD_PIPE			4

# define CMD_O_BRACKET		5
# define CMD_C_BRACKET		6

# define CMD_PIPELINE		7
# define CMD_GROUP			8

# define CMD_L_SCMD			9
# define CMD_L_CMD			10

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

typedef struct s_scmd_content
{
	int		type;
	t_list	*l_argv;
	t_list	*l_redir;
}	t_c_scmd;

typedef struct s_cmd_content
{
	int		type;
	t_list	*l_element;
}	t_c_cmd;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

t_c_scmd	*scmd_content(t_list *element);
t_c_scmd	*c_scmd_get(t_list **l_token);
void		c_scmd_destroy(void *c_element);

t_c_cmd		*cmd_content(t_list *pg);
int			cmd_type_get(t_list *token);
void		c_cmd_destroy(void *c_pg);

#endif
