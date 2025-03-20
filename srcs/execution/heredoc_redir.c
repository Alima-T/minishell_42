/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:54:30 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/20 12:39:25 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Input Redirection
 * Output Redirection
 */
int	setup_redirections(t_cmd *cmds)
{
	if (cmds->inp != STDIN_FILENO)
	{
		if (dup2(cmds->inp, STDIN_FILENO) == -1)
		{
			perror("dup2");
			return (1);
		}
		if (cmds->inp > 2)
			close(cmds->inp);
	}
	if (cmds->out != STDOUT_FILENO)
	{
		if (dup2(cmds->out, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (1);
		}
		if (cmds->out > 2)
			close(cmds->out);
	}
	if (set_redir(cmds) != 0)
		return (1);
	return (0);
}

/**
 * Handles heredoc input and writes to a temporary file
 * @param delimiter The string that terminates heredoc input
 * @return File descriptor for reading heredoc or -1 on error
 */
int	handle_heredoc(char *delimiter)
{
	char	*line;
	int		fd;
	char	*tmp_file;
	int		heredoc_status;
	pid_t	heredoc_pid;

	tmp_file = generate_heredoc_filename();
	if (!tmp_file)
		return (-1);
	fd = open(tmp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(tmp_file);
		return (-1);
	}
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
	{
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			line = readline("> ");
			if (!line)
			{
				close(fd);
				free(tmp_file);
				exit(0);
			}
			if (ft_strcmp(line, delimiter) == 0)
			{
				free(line);
				close(fd);
				free(tmp_file);
				exit(0);
			}
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
	}
	close(fd);
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
	fd = open(tmp_file, O_RDONLY);
	if (fd == -1)
	{
		free(tmp_file);
		return (-1);
	}
	unlink(tmp_file);
	free(tmp_file);
	return (fd);
}

/**

	* @brief Handles redirs in the given command and opens appropriate file
	descriptors.
 *
 * Supports three types of redirs:
 *
 * - "<"  : Input redir
 *
 * - ">"  : Output redir (overwrite)
 *
 * - ">>" : Output redir (append)
 *
 * @param cmds Command structure containing redir information.
 * @return 0 on success, -1 on error
 */
int	set_redir(t_cmd *cmds)
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
			tmp = tmp->next;
			continue ;
		}
		if (ft_strcmp(tmp->type, "<") == 0)
		{
			fd = open_helper(tmp->name, 'I');
			if (fd == -1)
				return (-1);
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				close(fd);
				return (-1);
			}
			close(fd);
		}
		else if (ft_strcmp(tmp->type, ">") == 0)
		{
			fd = open_helper(tmp->name, 'O');
			if (fd == -1)
				return (-1);
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				close(fd);
				return (-1);
			}
			close(fd);
		}
		else if (ft_strcmp(tmp->type, ">>") == 0)
		{
			fd = open_helper(tmp->name, 'A');
			if (fd == -1)
				return (-1);
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				close(fd);
				return (-1);
			}
			close(fd);
		}
		tmp = tmp->next;
	}
	return (0);
}

/**
 * Sets up heredocs for a command
 * @param cmds Command structure
 * @return 0 on success, -1 on error
 */
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
