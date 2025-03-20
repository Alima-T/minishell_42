/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:06:55 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/20 23:07:13 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Checks if the given argument is a redirection operator.
 * @param arg The argument string to check.
 * @return 1 if the argument is a redirection operator, 0 otherwise.
 */
int	is_redir(char *arg)
{
	if ((ft_strcmp(arg, ">") == 0) || (ft_strcmp(arg, ">>") == 0)
		|| (ft_strcmp(arg, "<") == 0) || (ft_strcmp(arg, "<<") == 0))
		return (1);
	return (0);
}

/**
 * Marks redirection flags in the argument list.
 * Sets the redir_flag for redirection operators and their following arguments.
 * @param args A pointer to the list of arguments.
 */
void	set_redirect(t_arg *args)
{
	while (args)
	{
		if (is_redir(args->arg_val) == 1)
		{
			args->redir_flag = 1;
			args->next->redir_flag = 2;
			args = args->next->next;
		}
		else if (args)
			args = args->next;
	}
}
