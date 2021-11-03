/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 21:27:45 by tjensen           #+#    #+#             */
/*   Updated: 2021/11/03 18:03:47 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */
# define ERROR	-1

# define PROMPT "$> "

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */
typedef struct s_token_content
{
	char	*string;
	int		type;
}	t_token_content;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

void	lexer_destroy_token_content(void *content);
t_list	*lexer(char *input);

#endif
