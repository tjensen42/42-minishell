#ifndef PRINTER_H
# define PRINTER_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include <stdio.h>
# include <stdbool.h>

# include "libft.h"
# include "global.h"

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

void	printer_token(t_list *l_token);

void	printer_scmd(t_list *l_scmd);
void	printer_scmd_structure(t_list *l_scmd);

void	printer_cmd(t_list *l_cmd);
void	printer_cmd_structure(t_list *l_cmd);

void	printer_scmd_pipeline(t_list *l_scmd_pipeline, bool newline);
void	printer_other(int type);

#endif