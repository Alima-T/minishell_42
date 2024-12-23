/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:28:37 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/23 14:58:43 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int print_msg(int return_val, char *message, int ext_stat)
// {
// 	// Print a formatted prefix "[minishell ]$ " to stderr
// 	// BEGIN(49, 32) and CLOSE could be macros that add color or special formatting.
// 	// 49: Default background color (terminal's default background).
// 	// 32: Green text color (foreground).
// 	// 9: Red background.
// 	// 15: White text.
// 	ft_putstr_fd(BEGIN(9, 15)"[minishell ]$ "CLOSE, STDERR_FILENO);
// 	ft_putendl_fd(message, STDERR_FILENO);	
// 	// Set the global variable g_ext_stats to the value of ext_stat
// 	// This is typically used to track the exit status of commands or errors.
// 	*exit_status() = ext_stat;	
// 	// Return the value of ret_val
// 	// This value is typically used to signal success or failure to the caller.
// 	return (return_val);
// }
int	print_msg(int return_val, char *message, int exit_stat)
{
	ft_putstr_fd(BEGIN(49, 32)"[minishell ]$ "CLOSE, STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	*exit_status() = exit_stat;
	return (return_val);
}