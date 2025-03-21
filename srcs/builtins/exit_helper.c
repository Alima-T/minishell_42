/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:43:06 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/21 19:44:57 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_numeric_str(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	handle_non_digit(t_shell *mini, char *str)
{
	exit_with_error(mini, str, "numeric argument required", 255);
}

void	silent_exit(t_shell *mini, int status)
{
	ft_putendl_fd(BEGIN "minishell-1.0$ " CLOSE "exit", STDIN_FILENO);
	free_shell_mem_enhanced(mini);
	env_destroy(&mini->env_dup);
	free(mini);
	exit(status);
}
