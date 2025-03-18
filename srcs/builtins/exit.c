/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:17:26 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/18 08:52:48 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Exits the shell with an error message
 *
 * @param mini Shell structure
 * @param arg Argument causing the error
 * @param msg Error message
 * @param status Exit status
 */
void	exit_with_error(t_shell *mini, char *arg, char *msg, int status)
{
	ft_putstr_fd(BEGIN "minishell: "CLOSE "exit: ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(msg, STDERR_FILENO);
	free_shell_mem_enhanced(mini);
	shell_level_down(mini);
	*get_exit_status() = status;
	exit(status);
}

/**
 * @brief Handles the case when no exit argument is provided
 *
 * @param mini Shell structure
 */
static void	handle_exit_no_args(t_shell *mini)
{
	int	exit_status;

	exit_status = *get_exit_status();
	free_shell_mem_enhanced(mini);
	shell_level_down(mini);
	exit(exit_status);
}

/**
 * @brief Safely converts a string to an unsigned char with bounds checking
 *
 * @param mini Shell structure for error handling
 * @param str String to convert
 * @return unsigned char Converted value
 */
static unsigned char	str_to_exit_code(t_shell *mini, char *str)
{
	int				i;
	int				sign;
	long long int	result;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * 10 + (str[i] - '0');
		else
			handle_non_digit(mini, str);
		i++;
	}
	return ((unsigned char)((result * sign) % 256));
}

/**
 * @brief Performs the actual exit operation with status
 *
 * @param mini Shell structure
 * @param exit_status Status code to exit with
 */
static void	perform_exit(t_shell *mini, int exit_status)
{
	free_shell_mem_enhanced(mini);
	shell_level_down(mini);
	exit(exit_status);
}

/**
 * @brief Built-in exit command to terminate the shell
 *
 * Handles shell termination with optional exit status. Prints "exit" message,
 * validates arguments, and performs cleanup before exiting.
 *
 * @param ac Argument count
 * @param av Arguments array (command and optional exit code)
 * @param mini Shell structure for cleanup
 * @return int Exit status (only returns if too many arguments)
 *
 * @note Only returns when there are too many arguments; otherwise exits
 */
int	builtin_exit(int ac, char *av[], t_shell *mini)
{
	int	exit_status;
	int	original_stdout;

	original_stdout = dup(STDOUT_FILENO);
	ft_putstr_fd("exit\n", original_stdout);
	close(original_stdout);
	if (ac == 1)
		handle_exit_no_args(mini);
	if (ac > 2)
	{
		ft_putstr_fd(BEGIN "minishell-1.0: "CLOSE "exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (!is_numeric_str(av[1]))
		exit_with_error(mini, av[1], "numeric argument required", 255);
	exit_status = str_to_exit_code(mini, av[1]);
	perform_exit(mini, exit_status);
	return (exit_status);
}
