/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:23:55 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/23 13:05:53 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_cmd(t_arg *args)
{
	t_arg	*tmp;
	int		count;

	if (!args)
		return (0);
	tmp = args;
	count = 1;
	if (ft_strcmp("|", tmp->arg_val) == 0)
		return (0);
	while (tmp->next)
	{
		tmp = tmp->next;
		if (ft_strcmp(tmp->arg_val, "|") == 0)
			return (count);
		count++;
	}
	return (count);
}

/*
t_arg *args Указатель на заголовок связанного списка ( t_arg структ), где каждый узел содерж аргумент ( arg_val) 
int lists_count Кол-во узлов (арг) в связанном списке, сколько элементов необходимо преобразовать в массив.
*/
char	**turn_cmd_to_array(t_arg *args, int lists_count)
{
	char	**args_array; // A pointer to an array of strings (to hold the command arguments)
	int		i;            // An index variable to track the current position in the array

	i = 0;
	args_array = (char **)malloc(sizeof(char *) * (lists_count + 1));
	if (!args_array)
		return (NULL);
	// Go to the linked list and copy its elements into the array
	while (args && (lists_count != 0)) // Continue until the list is empty or all elements are processed
	{
		args_array[i] = ft_strdup(args->arg_val); // Duplicate args string (from args->arg_val), store it in the array
		args = args->next;
		lists_count--;// Decrement the count of remaining elements
		i++;// Increment to move to the next array position
	}
	args_array[i] = NULL;
	return (args_array);// Return the created array of strings
}

t_cmd	*create_cmds_list(t_arg *args)
{
	int lists_count;
	t_cmd *element;
	
	element = (t_cmd *) malloc(sizeof(t_cmd));
	if (!element || !args)
		return (NULL);
	element->redir = NULL;
	element->redir = (struct s_redir *) redirect_process(&args);
	lists_count = find_cmd(args);
	element->command = turn_cmd_to_array(args, lists_count);
	element->inp = 0;
	element->out = 1;
	element->fork = 0;
	element->pipe_fd[0] = 0;
	element->pipe_fd[1] = 0;
	element->next = NULL;
	return (element);
}

void	add_cmd_lst_end(t_cmd **list, t_cmd *new) 
{
	t_cmd	*last;

	if (!list || !new)
		exit(EXIT_FAILURE);
	if (*list)
	{
		last = *list;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	else
		*list = new;
}