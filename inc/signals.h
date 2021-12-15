#ifndef SIGNALS_H
# define SIGNALS_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include <stdbool.h>

# include "libft.h"
# include "global.h"

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

void	signal_ctlc(int sig);
int		termios_change(bool echo_ctl_chr);

#endif
