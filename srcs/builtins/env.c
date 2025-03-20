/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:14:03 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/20 12:28:43 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Prints all environment variables with non-empty values
 *
 * This function implements the built-in 'env' command for a shell. It iterates
 * through the linked list of environment variables and prints each variable
 * that has a non-NULL and non-empty value in the format "KEY=VALUE". Each
 * variable is printed on a separate line. If the environment list is NULL,
 * an error message is displayed.
 *
 * @param env_dup Pointer to the linked list of environment variables
 *
 * @return int 0 on success, 1 if environment is not set (NULL)
 *
 * @note Variables with NULL values or empty string values are silently skipped
 * @note Variables are printed in the order they appear in the linked list
 */
int	builtin_env(t_env *env_dup)
{
	if (!env_dup)
	{
		ft_putstr_fd(BEGIN "minishell: "CLOSE "env: environment not set\n", \
			STDERR_FILENO);
		return (1);
	}
	while (env_dup)
	{
		if (env_dup->val && env_dup->val[0] != '\0')
		{
			ft_putstr_fd(env_dup->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd(env_dup->val, STDOUT_FILENO);
		}
		env_dup = env_dup->next;
	}
	return (0);
}
