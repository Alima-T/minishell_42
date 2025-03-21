/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_and_heredoc_handle.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:25:23 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/21 16:55:21 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	open_helper(char *path, char flag)
{
	int	fd;

	fd = -1;
	if (flag == 'I')
		fd = open(path, O_RDONLY);
	else if (flag == 'O')
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (flag == 'A')
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd(BEGIN "minishell: " CLOSE, STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		*get_exit_status() = 1;
	}
	return (fd);
}

static char	*join_filename_parts(char *pid_str, char *counter_str)
{
	char	*temp_path;
	char	*tmp1;
	char	*result;

	temp_path = ft_strjoin("/tmp/.heredoc_", pid_str);
	if (!temp_path)
		return (NULL);
	tmp1 = ft_strjoin(temp_path, "_");
	free(temp_path);
	if (!tmp1)
		return (NULL);
	result = ft_strjoin(tmp1, counter_str);
	free(tmp1);
	return (result);
}

char	*generate_heredoc_filename(void)
{
	static int	counter;
	char		*pid_str;
	char		*counter_str;
	char		*result;
	pid_t		pid;

	counter = 0;
	pid = getpid();
	counter++;
	pid_str = ft_itoa(pid);
	if (!pid_str)
		return (NULL);
	counter_str = ft_itoa(counter);
	if (!counter_str)
	{
		free(pid_str);
		return (NULL);
	}
	result = join_filename_parts(pid_str, counter_str);
	free(pid_str);
	free(counter_str);
	return (result);
}
