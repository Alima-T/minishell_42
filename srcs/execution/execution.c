/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:17:08 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/21 16:58:48 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	init_and_check_builtins(t_shell *mini)
{
	mini->builtin_cmds = init_builtin_cmds();
	if (!mini->builtin_cmds)
	{
		ft_putstr_fd(BEGIN "minishell: " CLOSE, STDERR_FILENO);
		ft_putendl_fd("failed to initialize built-in commands", STDERR_FILENO);
		*get_exit_status() = 1;
		return (1);
	}
	return (0);
}

static int	process_heredocs(t_shell *mini)
{
	t_cmd	*cmd;

	cmd = mini->cmds;
	while (cmd)
	{
		if (set_heredoc(cmd) != 0)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

static void	execute_command_set(t_shell *mini)
{
	if (mini->cmds && mini->cmds->next)
		execute_multiple_cmds(mini);
	else if (*(mini->cmds->cmd))
	{
		if (mini->cmds->inp == 0)
			mini->cmds->inp = STDIN_FILENO;
		if (mini->cmds->out == 0 || mini->cmds->out == 1)
			mini->cmds->out = STDOUT_FILENO;
		if (execute_single_cmd(mini->cmds, mini) != 0)
			*get_exit_status() = 1;
	}
}

void	execute_cmd(t_shell *mini)
{
	if (init_and_check_builtins(mini) != 0)
		return ;
	if (process_heredocs(mini) != 0)
	{
		free_builtin_cmds(mini->builtin_cmds);
		mini->builtin_cmds = NULL;
		*get_exit_status() = 1;
		return ;
	}
	execute_command_set(mini);
	free_builtin_cmds(mini->builtin_cmds);
	mini->builtin_cmds = NULL;
}
