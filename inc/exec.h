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
int		exec_scmd(t_list *scmd);
int		exec_scmd_preperation(t_list *scmd, char ***argv);
int		exec_scmd_exec(char **argv);
void	exec_scmd_exit(int status, char **argv);

// EXEC_PIPELINE
int		exec_pipeline(t_list *pipeline);

// EXEC_PIPELINE_UTILS
void	pipes_init(int pipes[2][2]);
void	pipes_set(int fd[2], int pipes[2][2], int i, bool last);
int		pipes_close_end(int pipe_end);
int		pipes_close(int	pipes[2][2], int i, bool last);

// EXEC_SCMD_UTILS
int		scmd_search_path(char **argv);

// EXEC_WAIT
int		exec_wait_pid(int last_pid);
int		exec_wait_for_all(int last_pid);

// EXEC_EXIT_STATUS
void	exit_status_set(int status);
int		exit_status_get(void);

#endif
