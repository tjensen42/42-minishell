#ifndef EXPAND_H
# define EXPAND_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include <stdbool.h>

# include "libft.h"
# include "global.h"
# include "cmd.h"

# define WILDCARD	-1
# define VAR_SPACE	-1

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// EXPAND_VAR_SPLIT
int		expand_var_token_list_split(t_list **l_token);

// EXPAND_VAR
int		expand_var_token_list(t_list *l_token);

// EXPAND_WILDCARD_UTILS
bool	expand_token_is_wildcard(t_list *token);
char	*expand_pattern_get(t_list *token);
char	*expand_wildcard_append_str(char *wildcard, t_list *token);
char	**expand_files_current_dir(void);
void	expand_lst_replace_connected(t_list **l_token, t_list *old,
			t_list *new);

// EXPAND_WILDCARD
int		expand_wildcard_list(t_list	**l_token, char **files);

// EXPAND
int		expand_var(t_c_scmd *c_scmd);
int		expand_wildcard(t_c_scmd *c_scmd);

#endif
