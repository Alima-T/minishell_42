/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_change.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:02:52 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/02 17:17:35 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Get the current shell level (SHLVL) from the duplicated environment variables
 * Convert the current level to an integer, decrement it by 1, and convert back to a string
 * Update the SHLVL value in the environment copy with the new decremented level
 * 
 */
void	shell_level_down(t_shell *shell_context)
{
	char	*current_level;
	char	*down_level;
	
	current_level = find_in_env(shell_context->env_dup, "SHLVL");
	down_level = ft_itoa(ft_atoi(current_level) - 1);
	change_val_in_env_dup(shell_context->env_dup, "SHLVL", down_level);
	free(down_level);
}
/**
 * Get the current shell level (SHLVL) from the duplicated environment variables
 * Convert the current level to an integer, increment it by 1, and convert back to a string
 * Update the SHLVL value in the environment copy with the new decremented level
 */
void	shell_level_up(t_shell *shell_context)
{
	char	*current_level;
	char	*up_level;

	current_level = find_in_env(shell_context->env_dup, "SHLVL");
	up_level = ft_itoa(ft_atoi(current_level) + 1);
	change_val_in_env_dup(shell_context->env_dup, "SHLVL", up_level);
	free(up_level);
}

