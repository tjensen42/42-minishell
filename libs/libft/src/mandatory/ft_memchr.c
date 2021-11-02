/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 13:06:25 by hepple            #+#    #+#             */
/*   Updated: 2021/10/21 10:42:13 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Function that scans the initial 'n' bytes of the memory area pointed to by
 * 's' for the first instance of 'c' and returns a pointer to this byte
 * (or NULL if no matching byte is found).
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char) c)
			return ((void *)&s[i]);
		i++;
	}
	return (NULL);
}
