/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:17:08 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/20 15:38:05 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Main command execution function that handles built-ins, signaks,
	and pipelines
 * @param mini Shell structure conatining commands and environment
 */
void	execute_cmd(t_shell *mini)
{
	t_cmd			*cmd;

	mini->builtin_cmds = init_builtin_cmds();
	if (!mini->builtin_cmds)
	{
		ft_putstr_fd(BEGIN "minishell: " CLOSE, STDERR_FILENO);
		ft_putendl_fd("failed to initialize built-in commands", STDERR_FILENO);
		*get_exit_status() = 1;
		return ;
	}
	cmd = mini->cmds;
	while (cmd)
	{
		if (set_heredoc(cmd) != 0)
		{
			return ;
		}
		cmd = cmd->next;
	}
	if (mini->cmds && mini->cmds->next)
		execute_multiple_cmds(mini);
	else
	{
		if (mini->cmds->inp == 0)
			mini->cmds->inp = STDIN_FILENO;
		if (mini->cmds->out == 0 || mini->cmds->out == 1)
			mini->cmds->out = STDOUT_FILENO;
		execute_single_cmd(mini->cmds, mini);
	}
	free_builtin_cmds(mini->builtin_cmds);
	mini->builtin_cmds = NULL;
}
