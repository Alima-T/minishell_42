/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:57:38 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/21 13:54:08 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	input_redir(char *filename)
{
	int	fd;

	fd = open_helper(filename, 'I');
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	output_redir(char *filename)
{
	int	fd;

	fd = open_helper(filename, 'O');
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	append_redir(char *filename)
{
	int	fd;

	fd = open_helper(filename, 'A');
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
