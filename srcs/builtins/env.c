/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:14:03 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/21 16:56:19 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
