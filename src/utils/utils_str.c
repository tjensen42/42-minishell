/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:57:17 by hepple            #+#    #+#             */
/*   Updated: 2022/01/17 15:57:21 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"

char	*str_append_str(char *str, char *append)
{
	char	*tmp;

	tmp = str;
	str = ft_strjoin(str, append);
	free(tmp);
	return (str);
}

char	*str_append_chr(char *str, char append)
{
	char	*new_str;
	int		i;

	if (str == NULL)
		return (NULL);
	new_str = malloc(ft_strlen(str) + 2);
	if (new_str != NULL)
	{
		i = 0;
		while (str[i])
		{
			new_str[i] = str[i];
			i++;
		}
		new_str[i] = append;
		new_str[i + 1] = '\0';
	}
	free(str);
	return (new_str);
}

char	str_last_chr(char *str)
{
	if (str[0] != '\0')
		return (str[ft_strlen(str) - 1]);
	else
		return ('\0');
}
