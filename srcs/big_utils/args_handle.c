/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:39:49 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/13 19:41:55 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Creates a new argument node with the given argument string.
 * Allocates memory for the new node and duplicates the argument string.
 * 
 * @param arg_str The argument string to be stored in the new node.
 * @param mini A pointer to the shell structure (not used in this function).
 * @return A pointer to the newly created argument node, or NULL if allocation fails.
 */
t_arg	*new_arg(char *arg_str, t_shell *mini)
{
	t_arg	*el;

	(void)mini;
	el = (t_arg *)malloc(sizeof(t_arg));
	if (!el)
		return (NULL);
	el->arg_val = ft_strdup(arg_str);
	el->redir_flag = 0;
	el->next = NULL;
	free(arg_str);
	return (el);
}

/**
 * Adds a new argument node to the end of the linked list.
 * If the list is empty, the new node becomes the head of the list.
 * 
 * @param lst A double pointer to the head of the list.
 * @param new A pointer to the new argument node to be added.
 */
void	add_arg_end(t_arg	**lst, t_arg *new)
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

/**
 * Deletes the first node in the argument list.
 * Frees the memory allocated for the argument string and the node itself.
 * 
 * @param args A double pointer to the head of the argument list.
 */
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

/**
 * Deletes a specific argument node and frees its memory.
 * 
 * @param lst A pointer to the argument node to be deleted.
 */
void	del_one(t_arg *lst)
{
	if (!lst)
		return ;
	free(lst->arg_val);
	lst->arg_val = NULL;
	free(lst);
	lst = NULL;
}

/**
 * Destroys the entire argument list by deleting each node.
 * Frees all allocated memory for the argument strings and nodes.
 * 
 * @param lst A double pointer to the head of the argument list.
 */
void	list_destroy(t_arg **lst)
{
	t_arg	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		del_one(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

