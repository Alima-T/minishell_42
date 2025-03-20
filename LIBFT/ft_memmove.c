/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:01:56 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/20 12:12:19 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	typedef unsigned char	byte;
	if (NULL == src && NULL == dst)
		return (dst);
	if (dst > src)
		while (len--)
			*((byte *)dst + len) = *((byte *)src + len);
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
