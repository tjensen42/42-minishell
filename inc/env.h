#ifndef ENV_H
# define ENV_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

#include <stdbool.h>

#include "libft.h"
#include "global.h"

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

int		env_init(void);
char	*env_get_value(char *name);

int		env_unset_var(char *name);
int		env_put_var(char *str);

#endif
