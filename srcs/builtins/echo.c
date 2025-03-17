/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:34:47 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/17 18:41:41 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Checks if an argument has the -n option format
 *
 * Validates if the argument is a valid -n option (contains only 'n' characters)
 *
 * @param arg the argument to check
 * @return true if it's a valid -n option, false otherwise
 */
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

/**
 * @brief Helper function to check if the next argument is adjacent
 *
 * Determines if args[i+1] should be considered adjacent to args[i]
 * (i.e., was originally part of the same token but was split during parsing)
 *
 * @param args array of arguments
 * @param i current argument index
 * @return true if args[i+1] should be considered adjacent to args[i]
 */
static bool	is_adjacent_arg(char **args, int i)
{
	bool	current_has_no_spaces;
	bool	next_has_no_spaces;

	if (!args[i + 1])
		return (false);
	current_has_no_spaces = (ft_strchr(args[i], ' ') == NULL);
	next_has_no_spaces = (ft_strchr(args[i + 1], ' ') == NULL);
	return (current_has_no_spaces && next_has_no_spaces);
}

/**
 * @brief Process arguments to determine where to start printing and if newline
 * is needed.
 *
 * @param args array of arguments
 * @param newline pointer to newline flag
 * @return int Index to start printing from
 */
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

/**
 * @brief Prints the arguments to standard output
 *
 * @param args arguments to print
 * @param start_idx index to start printing from
 * @param newline whether to add a newline at the end
 */
static void	print_echo_args(char **args, int start_idx, bool newline)
{
	int		i;
	bool	skip_space;

	i = start_idx;
	while (args[i])
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		skip_space = is_adjacent_arg(args, i);
		if (args[i + 1] && !skip_space)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
}

/**
 * @brief Implements the built-in echo command.
 * Prints the provided arguments to the standard output with appropriate spacing.
 * Handles the -n option to suppress the trailing newline.
 *
 * @param args array of command arguments
 * @return int 0 on success
 */
int	builtin_echo(char **args)
{
	int		start_idx;
	bool	newline;

	start_idx = process_echo_options(args, &newline);
	print_echo_args(args, start_idx, newline);
	return (0);
}
