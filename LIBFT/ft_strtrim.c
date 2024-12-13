/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:57:03 by aokhapki          #+#    #+#             */
/*   Updated: 2024/03/19 15:44:59 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	first;
	unsigned int	last;

	first = 0;
	last = ft_strlen(s1) - 1;
	if (ft_strlen(s1) <= 0)
		return (ft_strdup(""));
	while (ft_strchr(set, s1[first]) != NULL)
	{
		if (first++ > last)
			return (ft_strdup(""));
	}
	while (ft_strchr(set, s1[last]) != NULL)
	{
		if (last-- <= first)
			return (ft_strdup(""));
	}
	return (ft_substr(s1, first, last + 1 - first));
}
