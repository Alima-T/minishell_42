/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:39:49 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/21 17:19:22 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	del_first_node(t_arg **args)
{
	t_arg	*next;

	if (!args || !(*args))
		return ;
	next = (*args)->next;
	free((*args)->arg_val);
	(*args)->arg_val = NULL;
	free((*args));
	*args = next;
}

static void	del_one_arg(t_arg *lst)
{
	if (!lst)
		return ;
	free(lst->arg_val);
	lst->arg_val = NULL;
	free(lst);
	lst = NULL;
}

void	arglst_destroy(t_arg **lst)
{
	t_arg	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		del_one_arg(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

t_arg	*new_arg(char *arg_str, t_shell *mini)
{
	t_arg	*node;

	(void)mini;
	node = (t_arg *)malloc(sizeof(t_arg));
	if (!node)
		return (NULL);
	node->arg_val = ft_strdup(arg_str);
	node->redir_flag = 0;
	node->space_flag_arg = false;
	node->next = NULL;
	free(arg_str);
	return (node);
}

void	append_arg(t_arg **lst, t_arg *new)
{
	t_arg	*last;

	if (!lst || !new)
		exit(EXIT_FAILURE);
	if (*lst)
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	else
		*lst = new;
}
