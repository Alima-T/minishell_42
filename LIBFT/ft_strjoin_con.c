/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_con.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:35:24 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/19 09:02:07 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_con(char const *s1, char *connector, char const *s2)
{
	char	*str;
	size_t	x;
	size_t	y;

	if (!s1 || !connector || !s2)
		return (NULL);
	str = (char *) malloc(sizeof(char) * 
			(ft_strlen(s1) + ft_strlen(connector) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	x = 0;
	y = 0;
	while (s1[y])
		str[x++] = s1[y++];
	y = 0;
	while (connector[y])
		str[x++] = connector[y++];
	y = 0;
	while (s2[y])
		str[x++] = s2[y++];
	str[x] = '\0';
	return (str);
}