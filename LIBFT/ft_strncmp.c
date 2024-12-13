/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:32:42 by aokhapki          #+#    #+#             */
/*   Updated: 2024/03/25 11:32:42 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t byte_n)
{
	size_t	i;

	i = 0;
	if (byte_n == 0)
		return (0);
	while (s1[i] != '\0' && s1[i] == s2[i] && i < byte_n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
