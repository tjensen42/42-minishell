/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_gnl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:56:21 by hepple            #+#    #+#             */
/*   Updated: 2022/01/17 15:56:30 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"

static char	*minishell_gnl_free_line(char *line);

char	*minishell_get_next_line(int fd)
{
	char	*line;
	char	buffer;
	int		check;

	line = ft_strdup("");
	if (line == NULL)
		return (NULL);
	check = read(fd, &buffer, 1);
	if (check == -1 || check == 0)
		return (minishell_gnl_free_line(line));
	while (check > 0)
	{
		line = str_append_chr(line, buffer);
		if (line == NULL)
			return (NULL);
		if (buffer == '\n')
			return (line);
		check = read(fd, &buffer, 1);
	}
	if (check == -1)
		return (minishell_gnl_free_line(line));
	return (line);
}

static char	*minishell_gnl_free_line(char *line)
{
	free(line);
	return (NULL);
}
