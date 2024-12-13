/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:01:56 by aokhapki          #+#    #+#             */
/*   Updated: 2024/03/25 10:59:21 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    *ft_memmove(void *dst, const void *src, size_t len)
{
    typedef unsigned char byte;
    if (NULL == src && NULL == dst)
        return (dst);
    if (dst > src)
        while (len--)
            *((byte *)dst + len) = *((byte *)src + len);
    else
        ft_memcpy(dst, src, len);
    return (dst);
}
