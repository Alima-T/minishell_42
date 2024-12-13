/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 08:01:12 by aokhapki          #+#    #+#             */
/*   Updated: 2024/03/27 11:06:44 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lstdub;

	lstdub = *lst;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	if (!new)
		return ;
	while (lstdub->next)
		lstdub = lstdub->next;
	lstdub->next = new;
}
