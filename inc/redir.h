#ifndef REDIR_H
# define REDIR_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>

# include "libft.h"
# include "global.h"
# include "token.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

// REDIR_TYPES
# define REDIR_OUT		1
# define REDIR_OUT_APP	2
# define REDIR_IN		3
# define REDIR_HEREDOC	4

// REDIR_FDs
# define REDIR_FILE		0
# define REDIR_NUM		1

// REDIR_FD_BUILTIN
# define REDIR_FD_OLD	0
# define REDIR_FD_NEW	1

typedef struct s_redir_undo_content
{
	int		fd_replaced;
	int		fd_replaced_dup;
	char	*here_doc_file;
}	t_c_redir_undo;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// EXEC_REDIR
int	redir(t_list *l_token, t_list **l_undo);
int	redir_type(char *redir);
int	redir_undo(t_list **l_undo);

#endif
