/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:03:13 by aokhapki          #+#    #+#             */
/*   Updated: 2024/03/16 17:03:13 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int symbol)
{
	unsigned char	chr;
	size_t			length;

	length = ft_strlen(s) + 1;
	chr = (unsigned char)symbol;
	while (length)
	{
		if (s[--length] == chr)
			return ((char *)(s + length));
	}
	return (NULL);
}
