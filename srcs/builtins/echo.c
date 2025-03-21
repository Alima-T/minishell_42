/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:34:47 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/21 16:56:15 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	is_n_option(char *arg)
{
	int	j;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (false);
	j = 2;
	while (arg[j] == 'n')
		j++;
	return (arg[j] == '\0');
}

static int	process_echo_options(char **args, bool *newline)
{
	int	i;

	i = 1;
	*newline = true;
	while (args[i] && is_n_option(args[i]))
	{
		*newline = false;
		i++;
	}
	return (i);
}

static void	print_echo_args(char **args, int start_idx, bool newline,
		t_arg *orig_args)
{
	int		i;
	t_arg	*current;

	current = orig_args;
	i = start_idx;
	while (args[i])
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (args[i + 1] && current)
		{
			if (current->space_flag_arg)
				write(STDOUT_FILENO, " ", 1);
		}
		i++;
		if (current)
			current = current->next;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
}

int	builtin_echo(char **args, t_arg *orig_args)
{
	int		start_idx;
	bool	newline;
	t_arg	*current;
	int		i;

	start_idx = process_echo_options(args, &newline);
	current = orig_args;
	i = 0;
	while (current && i < start_idx)
	{
		current = current->next;
		i++;
	}
	print_echo_args(args, start_idx, newline, current);
	return (0);
}
