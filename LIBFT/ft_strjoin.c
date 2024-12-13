/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:55:04 by aokhapki          #+#    #+#             */
/*   Updated: 2024/03/15 18:26:19 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	char	*pnew_s;

	new_s = (char *)malloc(ft_strlen(s1) + (ft_strlen(s2)+ 1));
	if (!new_s)
		return (NULL);
	pnew_s = new_s;
	while (*s1)
	{
		*new_s = *s1;
		new_s++;
		s1++;
	}
	while (*s2)
	{
		*new_s = *s2;
		new_s++;
		s2++;
	}
	*new_s = '\0';
	return (pnew_s);
}
