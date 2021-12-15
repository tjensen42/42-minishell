#ifndef EXPAND_H
# define EXPAND_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include <stdbool.h>

# include "libft.h"
# include "global.h"
# include "cmd.h"


# define WILDCARD	 -1

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

int		expand_var_scmd(t_c_scmd *c_scmd);
int		expand_wildcard(t_c_scmd *c_scmd);

bool	expand_token_is_wildcard(t_list *token);
char	*expand_wildcard_get(t_list *token);
char	*expand_wildcard_append_str(char *wildcard, t_list *token);
char	**expand_fname_get(void);

#endif
