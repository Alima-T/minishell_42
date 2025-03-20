/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:33:23 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/20 13:16:40 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	redir_add_end(t_redir **list, t_redir *new)
{
	t_redir	*last;

	if (!list || !new)
		exit(EXIT_FAILURE);
	if (*list == NULL)
		*list = new;
	else
	{
		last = *list;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

// Function to create a new redirection
t_redir	*redir_new(char *type, char *name)
{
	t_redir	*new_redir;

	new_redir = (t_redir *)malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->type = ft_strdup(type);
	new_redir->name = ft_strdup(name);
	new_redir->next = NULL;
	return (new_redir);
}

/**
 обрабатывает список аргументов ( t_arg связанный список) и обрабатывает
 флаги перенаправления, обновляя список перенаправления ( t_redir).
 */
// Function to handle the first redirection
int	redir_first(t_arg **args, t_redir **rdr)
{
	while (*args)
	{
		if ((*args)->redir_flag == 1)
		{
			redir_add_end(rdr, redir_new((*args)->arg_val,
					(*args)->next->arg_val));
			if (!(*args)->next->next)
			{
				(*args) = (*args)->next->next;
				return (1);
			}
			(*args) = (*args)->next->next;
		}
		if ((*args)->redir_flag == 0)
			break ;
	}
	return (0);
}

// Function to add a new redirection to the end of the list
t_redir	*redirect_process(t_arg **args)
{
	t_arg	*tmp;
	t_redir	*rdr;

	if (!args || !(*args))
		return (NULL);
	rdr = NULL;
	if (redir_first(args, &rdr) == 1)
		return (rdr);
	tmp = *args;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->arg_val, "|") == 0)
			break ;
		if (tmp->next->redir_flag == 1)
		{
			redir_add_end(&rdr, redir_new(tmp->next->arg_val,
					tmp->next->next->arg_val));
			del_first_node(&tmp->next);
			del_first_node(&tmp->next);
		}
		if (tmp->next && tmp->next->redir_flag != 1)
			tmp = tmp->next;
	}
	return (rdr);
}
