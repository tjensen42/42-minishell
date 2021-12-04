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
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

int	execution_recursive(t_list *l_cmd);

// EXEC_SCMD
int	execution_scmd(t_list *scmd, bool pipeline);

// EXEC_PIPELINE
int	exec_pipeline(t_list *pipeline);

// EXEC_PIPES
void	pipes_init(int pipes[2][2]);
void	child_set_pipes(int fd[2], int pipes[2][2], int i, bool last);
int		close_pipe_end(int pipe_end);
int		close_pipes(int	pipes[2][2], int i, bool last);

// EXEC_SCMD_UTILS
int		scmd_set_path(char **argv);
char	**l_token_to_split(t_list *l_token);

#endif
