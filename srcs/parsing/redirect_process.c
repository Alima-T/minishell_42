/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:33:23 by aokhapki          #+#    #+#             */
/*   Updated: 2025/02/10 20:51:08 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 обрабатывает список аргументов ( t_arg связанный список) и обрабатывает флаги перенаправления,
обновляя список перенаправления ( t_redir).
 */
// Function to handle the first redirection
int	redir_first(t_arg **args, t_redir **rdr)
{
	t_redir	*new_redirection;

	// Example logic to handle the first redirection
	if (args == NULL || *args == NULL)
		return (-1); // Return an error if args is NULL
	// Here you would implement logic to process the first argument
	// and create a new redirection based on it
	// For example:
	new_redirection = redir_new("<<", "a"); // Example redirection
	if (new_redirection == NULL)
		return (-1);                     // Return an error if allocation fails
	redir_add_end(rdr, new_redirection); // Add the new redirection to the list
	return (0);                          // Return success
}

// Function to create a new redirection
t_redir	*redir_new(char *type, char *name)
{
	t_redir	*new_redir;

	// Allocate memory for the new redirection
	new_redir = (t_redir *)malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL); // Return NULL if allocation fails
	// Assign values to the new redirection
	new_redir->type = ft_strdup(type); // Duplicate the type string
	new_redir->name = ft_strdup(name); // Duplicate the name string
	new_redir->next = NULL;            // Initialize the next pointer to NULL
	return (new_redir);                // Return the new redirection
}

// Function to add a new redirection to the end of the list
void	redir_add_end(t_redir **list, t_redir *new)
{
	t_redir	*last;

	if (!list || !new)
		return ; // Do nothing if the list or new redirection is NULL
	if (*list == NULL)
	{
		*list = new; // If the list is empty,
						// set the new redirection as the head
	}
	else
	{
		last = *list;
		while (last->next)
			last = last->next; // Traverse to the end of the list
		last->next = new;      // Add the new redirection at the end
	}
}

t_redir	*redirect_process(t_arg **args)
{
	t_arg *tmp;   // Temporary ptr for args list.
	t_redir *rdr; // Ptr to the redir list.
	if (!args || !(*args))
		return (NULL);
	rdr = NULL;
	// Process the first redir in the argument list.
	// If redir_first returns 1, it indicates a complete redir was processed.
	if (redir_first(args, &rdr) == 1)
		return (rdr); // Return the current redir list.
	tmp = *args;      // Set tmp to point to the head of the argument list.
	// Traverse the argument list until the end or a pipe (`|`) is encountered.
	while (tmp->next)
	{
		if (ft_strcmp(tmp->arg_val, "|") == 0)
			// If the current argument's value is a pipe (`|`), stop processing.
			break ;
		if (tmp->next->redir_flag == 1)
			// If the next argument has a redir flag (e.g., >, >>, <, etc.):
			// Add a new redir node to the redir list.
			// The redir type (tmp->next->arg_val) and its target (tmp->next->next->arg_val)
			// are passed to create the redir node.
			redir_add_end(&rdr, redir_new(tmp->next->arg_val,
					tmp->next->next->arg_val));
		/* Move to the next argument if it doesn't have a redir flag.
		This prevents redundant checks for already processed redirs.
		Условие if (tmp->next && tmp->next->redir_flag != 1)гарантирует,
			что цикл перейдет к следующему узлу,
			если текущий узел не указывает на перенаправление.
		Правильное объяснение:
		Это не предотвращает избыточные проверки уже обработанных перенаправлений ,
			а скорее:Гарантирует продолжение обхода по связанному списку,
			даже если текущий аргумент не представляет собой перенаправление.
		Пропускает узлы, которые не вызывают срабатывание redir_flag == 1. */
		if (tmp->next && tmp->next->redir_flag != 1)
			tmp = tmp->next;
	}
	return (rdr);
}
