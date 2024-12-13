/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:26:27 by aokhapki          #+#    #+#             */
/*   Updated: 2024/03/27 12:11:32 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	h_get_length(int n)
{
	int	length;

	length = 0;
	if (n == 0)
		return (1);
	n = -n;
	while (n != 0)
	{
		n /= 10;
		length++;
	}
	return (length);
}

int	h_make_positive(int n)
{
	if (n < 0)
		n = -n;
	return (n);
}

char	*ft_itoa(int n)
{
	int		i;
	int		length;
	char	*str;

	i = 0;
	if (n < 0)
		i = 1;
	length = h_get_length(n) + i;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = (char *)malloc(sizeof(char) * (length + 1));
	if (str == NULL)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	str[length] = '\0';
	n = h_make_positive (n);
	while (i != length--)
	{
		str[length] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
