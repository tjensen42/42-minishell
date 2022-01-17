/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:29:48 by hepple            #+#    #+#             */
/*   Updated: 2022/01/17 15:29:49 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	*exec_exit_status_pointer(void);

int	exec_exit_status_get(void)
{
	return (*exec_exit_status_pointer());
}

void	exec_exit_status_set(int status)
{
	if (status == ERROR)
		status = EXIT_FAILURE;
	*exec_exit_status_pointer() = status;
}

static int	*exec_exit_status_pointer(void)
{
	static int	last_exit_status = 0;

	return (&last_exit_status);
}
