/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 08:02:57 by aokhapki          #+#    #+#             */
/*   Updated: 2024/03/27 11:14:39 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lst_dub;

	if (!lst || !del || !*lst)
		return ;
	while (*lst)
	{
		lst_dub = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = lst_dub;
	}
	*lst = NULL;
}
