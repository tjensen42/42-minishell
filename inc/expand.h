/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:01:34 by tjensen           #+#    #+#             */
/*   Updated: 2022/01/17 16:01:35 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "global.h"
# include "cmd.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

# define WILDCARD	-1
# define VAR_SPACE	-1

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// EXPAND
int		expand_var(t_c_scmd *c_scmd);
int		expand_wildcard(t_c_scmd *c_scmd);

// EXPAND_VAR_SPLIT
int		expand_var_splitting(t_list **l_token);

// EXPAND_VAR
int		expand_var_token_list(t_list *l_token);

// EXPAND_WILDCARD_UTILS
bool	expand_token_is_wildcard(t_list *token);
char	*expand_pattern_get(t_list *token);
char	*expand_wildcard_append_str(char *wildcard, t_list *token);
char	**expand_files_current_dir(void);
void	expand_wildcard_replace_connected(t_list **l_token, t_list *old,
			t_list *new);

// EXPAND_WILDCARD
int		expand_wildcard_list(t_list	**l_token, char **files);

#endif
