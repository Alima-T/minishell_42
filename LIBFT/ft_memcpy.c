/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:01:33 by aokhapki          #+#    #+#             */
/*   Updated: 2024/03/25 11:40:53 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t byte_n)
{
	char		*temp_dest;
	const char	*temp_src;

	temp_dest = dest;
	temp_src = src;
	if (dest == 0 && src == 0)
		return (NULL);
	while (byte_n--)
		*temp_dest++ = *temp_src++;
	return (dest);
}
