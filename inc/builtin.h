#ifndef BUILTIN_H
# define BUILTIN_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include <stdio.h>

# include "global.h"

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

struct s_builtins
{
	char	*name;
	int		(*func)(int argc, char **argv);
};

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

int	builtin_check(char **argv);
int	builtin_exec(char **argv, bool subshell, t_list *l_free);

int	builtin_echo(int argc, char **argv);
int	builtin_env(int argc, char **argv);
int	builtin_exit(int argc, char **argv, bool subshell, t_list *l_free);
int	builtin_pwd(int argc, char **argv);
int	builtin_cd(int argc, char **argv);
int	builtin_export(int argc, char **argv);
int	builtin_unset(int argc, char **argv);

#endif
