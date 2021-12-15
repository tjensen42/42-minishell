#ifndef EXPAND_H
# define EXPAND_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include <stdbool.h>

# include "libft.h"
# include "global.h"
# include "cmd.h"

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

int	expand_var_scmd(t_c_scmd *c_scmd);
int	expand_wildcard(t_c_scmd *c_scmd);

#endif
