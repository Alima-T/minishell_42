/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:25:52 by aokhapki          #+#    #+#             */
/*   Updated: 2024/03/20 15:02:33 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
	{
	void	*memory;
	size_t	length;

	length = count * size;
	memory = malloc(length);
	if (memory == NULL)
		return (NULL);
	ft_bzero(memory, length);
	return (memory);
}
