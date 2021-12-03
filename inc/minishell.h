/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 21:27:45 by tjensen           #+#    #+#             */
/*   Updated: 2021/12/03 10:06:28 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "libft.h"
# include "global.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

# define ERROR		-1
# define PROMPT 	"$> "

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

t_list	*lexer(char *input);

#endif
