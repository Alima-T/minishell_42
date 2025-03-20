/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:01:56 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/20 22:54:32 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	*ft_memmove(void *dst, const void *src, size_t len)
// {
// 	typedef unsigned char	byte;
// 	if (NULL == src && NULL == dst)
// 		return (dst);
// 	if (dst > src)
// 		while (len--)
// 			*((byte *)dst + len) = *((byte *)src + len);
// 	else
// 		ft_memcpy(dst, src, len);
// 	return (dst);
// }

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char	*source1;
	char		*dest1;

	dest1 = dst;
	source1 = src;
	if (dest1 < source1)
	{
		while (len > 0)
		{
			*dest1++ = *source1++;
			len--;
		}
	}
	else if (dest1 > source1)
	{
		dest1 += len;
		source1 += len;
		while (len > 0)
		{
			*(--dest1) = *(--source1);
			len--;
		}
	}
	return (dst);
}
