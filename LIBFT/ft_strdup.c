/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:02:57 by aokhapki          #+#    #+#             */
/*   Updated: 2024/03/26 08:08:50 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*new_str;
	size_t	new_len;

	new_len = ft_strlen(s1);
	new_str = malloc(new_len + 1);
	if (!new_str)
		return (NULL);
	return (ft_memcpy(new_str, s1, new_len + 1));
}
// creat new mem and copy(duplicate) given string in a new mem
