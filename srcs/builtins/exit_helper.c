/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:43:06 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/17 18:43:39 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Checks if a string contains only numeric characters
 *
 * @param str String to check
 * @return int 1 if numeric, 0 otherwise
 */
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

/**
 * @brief Processes a non-digit character in exit code conversion
 *
 * @param mini Shell structure
 * @param str String being converted
 */
void	handle_non_digit(t_shell *mini, char *str)
{
	exit_with_error(mini, str, "numeric argument required", 255);
}
