/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:01:28 by tjensen           #+#    #+#             */
/*   Updated: 2022/01/17 16:01:29 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTER_H
# define PRINTER_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include <stdio.h>

# include "global.h"
# include "cmd.h"

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// PRINTER_CMD
void	printer_cmd(t_list *l_cmd);
void	printer_structure(t_list *l_cmd);

// PRINTER_SCMD
void	printer_scmd(t_c_scmd *scmd);
void	printer_other(int type);
void	printer_scmd_pipeline(t_list *l_scmd_pipeline, bool newline);

// PRINTER_TOKEN
void	printer_token(t_list *l_token);

#endif
