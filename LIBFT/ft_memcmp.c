/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:24:24 by aokhapki          #+#    #+#             */
/*   Updated: 2024/03/25 11:24:24 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t byte_n)
{
	char	*ch_str1;
	char	*ch_str2;
	size_t	i;

	i = 0;
	ch_str1 = (char *)s1;
	ch_str2 = (char *)s2;
	while (i < byte_n)
	{
		if (ch_str1[i] != ch_str2[i])
			return ((unsigned char)ch_str1[i] - (unsigned char)ch_str2[i]);
		i++;
	}
	return (0);
}

/* memcmp() compare first n bytes of memory s1 & s2.
* returns zero if the two strings are identical
* return the difference between the two differing unsigned char casted bytes. 
* If i reaches the point where it is no longer less than n and we
* have still not found any differing bytes we will return a 0
*/