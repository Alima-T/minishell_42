/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:33:23 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/20 15:17:10 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 обрабатывает список аргументов ( t_argсвязанный список) и обрабатывает флаги перенаправления, обновляя список перенаправления ( t_redir). 
 * 
 */
int	redir_first (t_arg **args, t_redir **rdr)
{
	return (0);
}

t_redir	*redir_new(char *type, char *name)
{
	t_redir	*element;
}

void	redir_add_end(t_redir **list, t_redir *new)
{

}

t_redir	*redirect_process(t_arg **args)
{
	t_arg	*tmp;       // Temporary ptr for args list.
	t_redir	*rdr;       // Ptr to the redir list.

	if (!args || !(*args))
		return (NULL);
	rdr = NULL; 
	// Process the first redir in the argument list.
	// If redir_first returns 1, it indicates a complete redir was processed.
	if (redir_first(args, &rdr) == 1)
		return (rdr); // Return the current redir list.
	tmp = *args; // Set tmp to point to the head of the argument list.
	// Traverse the argument list until the end or a pipe (`|`) is encountered.
	while (tmp->next)
	{
		if (ft_strcmp(tmp->arg_val, "|") == 0)	// If the current argument's value is a pipe (`|`), stop processing.
			break;
		if (tmp->next->redir_flag == 1)	// If the next argument has a redir flag (e.g., >, >>, <, etc.):
			// Add a new redir node to the redir list.
			// The redir type (tmp->next->arg_val) and its target (tmp->next->next->arg_val)
			// are passed to create the redir node.
			redir_add_end(&rdr, redir_new(tmp->next->arg_val, tmp->next->next->arg_val));
/* Move to the next argument if it doesn't have a redir flag.
This prevents redundant checks for already processed redirs.
Условие if (tmp->next && tmp->next->redir_flag != 1)гарантирует, что цикл перейдет к следующему узлу, если текущий узел не указывает на перенаправление.
Правильное объяснение:
Это не предотвращает избыточные проверки уже обработанных перенаправлений , а скорее:Гарантирует продолжение обхода по связанному списку, даже если текущий аргумент не представляет собой перенаправление.
Пропускает узлы, которые не вызывают срабатывание redir_flag == 1. */
		if (tmp->next && tmp->next->redir_flag != 1)
			tmp = tmp->next;
	}
	return (rdr);
}

