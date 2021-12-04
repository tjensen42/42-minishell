#ifndef EXEC_H
# define EXEC_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "libft.h"
#include "global.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

// POSIX BASED EXIT STATUS
#define EX_NOEXEC	126
#define EX_NOTFOUND	127

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// EXEC
int	exec_recursive(t_list *l_cmd);

// EXEC_SCMD
int	exec_scmd(t_list *scmd);

// EXEC_PIPELINE
int	exec_pipeline(t_list *pipeline);

// EXEC_PIPELINE_UTILS
void	pipes_init(int pipes[2][2]);
void	pipes_child_set(int fd[2], int pipes[2][2], int i, bool last);
int		pipes_close_end(int pipe_end);
int		pipes_close(int	pipes[2][2], int i, bool last);

// EXEC_SCMD_UTILS
int		scmd_search_path(char **argv);
char	**l_token_to_split(t_list *l_token);

#endif
