/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:54:30 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/21 16:59:07 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	create_heredoc_file(char **tmp_file)
{
	int	fd;

	*tmp_file = generate_heredoc_filename();
	if (!*tmp_file)
		return (-1);
	fd = open(*tmp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(*tmp_file);
		*tmp_file = NULL;
		return (-1);
	}
	return (fd);
}

static pid_t	fork_heredoc_process(int fd, char *tmp_file, char *delimiter)
{
	pid_t	heredoc_pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	heredoc_pid = fork();
	if (heredoc_pid == -1)
	{
		close(fd);
		free(tmp_file);
		return (-1);
	}
	if (heredoc_pid == 0)
		process_heredoc_input(fd, tmp_file, delimiter);
	return (heredoc_pid);
}

static int	wait_heredoc_process(pid_t heredoc_pid, char *tmp_file)
{
	int	heredoc_status;

	waitpid(heredoc_pid, &heredoc_status, 0);
	signal(SIGINT, sig_non_interact_ctrl_c);
	signal(SIGQUIT, sig_non_interact_quit);
	if (WIFSIGNALED(heredoc_status))
	{
		unlink(tmp_file);
		free(tmp_file);
		*get_exit_status() = 130;
		return (-1);
	}
	return (0);
}

int	handle_heredoc(char *delimiter)
{
	char	*tmp_file;
	int		fd;
	pid_t	heredoc_pid;

	fd = create_heredoc_file(&tmp_file);
	if (fd == -1)
		return (-1);
	heredoc_pid = fork_heredoc_process(fd, tmp_file, delimiter);
	if (heredoc_pid == -1)
		return (-1);
	close(fd);
	if (wait_heredoc_process(heredoc_pid, tmp_file) == -1)
		return (-1);
	return (open_heredoc_for_reading(tmp_file));
}

int	set_heredoc(t_cmd *cmds)
{
	t_redir	*tmp;
	int		fd;

	if (!cmds)
		return (0);
	tmp = (t_redir *)cmds->redir;
	while (tmp)
	{
		if (ft_strcmp(tmp->type, "<<") == 0)
		{
			fd = handle_heredoc(tmp->name);
			if (fd == -1)
				return (-1);
			if (cmds->inp != STDIN_FILENO && cmds->inp > 0)
				close(cmds->inp);
			cmds->inp = fd;
		}
		tmp = tmp->next;
	}
	return (0);
}
