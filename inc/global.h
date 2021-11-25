#ifndef GLOBAL_H
# define GLOBAL_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include <unistd.h>

# include "libft.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

# define ERROR				-1

# define ERR_NO_MEM			"minishell: out of virtual memory"

/* ************************************************************************** */
/* GLOBAL VARIABLES															  */
/* ************************************************************************** */

extern char	**g_env;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

int		print_error(char *str);
int		count_str_array(char **argv);

int		lst_node_remove(t_list **lst, t_list *node, void (*del)(void *));
t_list	*lst_node_prev(t_list *lst, t_list *node);
int		lst_relink(t_list **lst, t_list *node, t_list *start, t_list *end);

int		split_append_str(char ***split, char *str);
int		split_replace_str_i(char ***split, int i, char *new);

#endif
