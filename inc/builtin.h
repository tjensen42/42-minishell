/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:01:00 by tjensen           #+#    #+#             */
/*   Updated: 2022/01/30 09:50:19 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// BUILTIN
int	builtin_check(char **argv);
int	builtin_exec(char **argv, bool subshell, t_list *l_free);

// BUILTIN_CD
int	builtin_cd(int argc, char **argv);

// BUILTIN_ECHO
int	builtin_echo(int argc, char **argv);

// BUILTIN_ENV
int	builtin_env(int argc, char **argv);

// BUILTIN_EXIT
int	builtin_exit(int argc, char **argv, bool subshell, t_list *l_free);

// BUILTIN_EXPORT
int	builtin_export(int argc, char **argv);

// BUILTIN_PWD
int	builtin_pwd(int argc, char **argv);

// BUILTIN_UNSET
int	builtin_unset(int argc, char **argv);

#endif
