/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:43:15 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/17 18:47:57 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Implements the built-in pwd (print working directory) command
 *
 * Gets the current working directory using getcwd() and prints it to
 * standard output. If the operation fails, prints the error message
 * to standard error.
 *
 * @return int 0 on success, 1 on error
 */
int	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (0);
	}
	else
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (1);
	}
}
