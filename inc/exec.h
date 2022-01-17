#ifndef EXEC_H
# define EXEC_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "libft.h"
# include "global.h"
# include "redir.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

// POSIX BASED EXIT STATUS
# define EXEC_NOEXEC	126
# define EXEC_NOTFOUND	127

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// EXEC
int		exec_recursive(t_list *l_cmd, bool subshell, t_list *l_free);
void	exec_free_all(char **argv, t_list *l_free);

// EXEC_SCMD
int		exec_scmd(t_list *scmd, bool subshell, t_list *l_free);
int		exec_scmd_preperation(t_list *scmd, char ***argv);
int		exec_scmd_exec(char **argv);
void	exec_scmd_exit(int status, char **argv, t_list *l_free);

// EXEC_PIPELINE
int		exec_pipeline(t_list *pipeline, t_list *l_free);

// EXEC_PIPELINE_UTILS
void	pipes_init(int pipes[2][2]);
void	pipes_set(int fd[2], int pipes[2][2], int i, bool last);
int		pipes_close_end(int pipe_end);
void	pipes_close(int	pipes[2][2], int i, bool last);

// EXEC_SCMD_UTILS
int		scmd_search_path(char **argv);

// EXEC_WAIT
int		exec_wait_pid(int last_pid, char *name);
int		exec_wait_for_all(int last_pid);

// EXEC_EXIT_STATUS
void	exit_status_set(int status);
int		exit_status_get(void);

#endif
