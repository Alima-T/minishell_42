/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:12:17 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/21 16:59:23 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	help_setup_redirections(t_cmd *cmds)
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

static int	process_redir(t_redir *redir)
{
	if (ft_strcmp(redir->type, "<<") == 0)
		return (0);
	if (ft_strcmp(redir->type, "<") == 0)
		return (input_redir(redir->name));
	else if (ft_strcmp(redir->type, ">") == 0)
		return (output_redir(redir->name));
	else if (ft_strcmp(redir->type, ">>") == 0)
		return (append_redir(redir->name));
	return (0);
}

int	set_redir(t_cmd *cmds)
{
	t_redir	*tmp;

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
		if (process_redir(tmp) == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}
