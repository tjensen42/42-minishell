#ifndef BUILTIN_H
# define BUILTIN_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

#include <stdbool.h>

#include "libft.h"
#include "global.h"

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

int builtin_echo(char **argv);
int	builtin_env(void);
int	builtin_exit(char **argv);
int	builtin_pwd(void);

#endif
