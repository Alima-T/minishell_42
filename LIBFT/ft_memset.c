/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:00:30 by aokhapki          #+#    #+#             */
/*   Updated: 2024/03/25 11:25:45 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int value, size_t byte_n)
{
	char	*temp;

	if (dest == 0 && byte_n == 0)
		return (NULL);
	temp = dest;
	while (byte_n--)
		*temp++ = value;
	return (dest);
}
