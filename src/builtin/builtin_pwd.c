/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:13:57 by hepple            #+#    #+#             */
/*   Updated: 2022/01/17 15:13:58 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_pwd(int argc __attribute((unused)),
	char **argv __attribute((unused)))
{
	char	buf[PATH_MAX];

	if (getcwd(buf, sizeof(buf)))
	{
		ft_putendl_fd(buf, STDOUT_FILENO);
		return (0);
	}
	else
	{
		print_error_errno(SHELL_NAME, "pwd", NULL);
		return (EXIT_FAILURE);
	}
}
