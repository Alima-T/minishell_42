/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:51:57 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/20 12:05:29 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	validate_input(t_shell *mini)
{
	if (validator(mini->input) == 0)
	{
		mini->args = args_process(mini);
		if (!mini->args)
		{
			free(mini->input);
			mini->input = NULL;
			return (1);
		}
		mini->cmds = cmds_process(mini);
		if (!mini->cmds && mini->args)
		{
			arglst_destroy(&mini->args);
			free(mini->input);
			mini->input = NULL;
			return (1);
		}
	}
	else
	{
		*get_exit_status() = 2;
		free(mini->input);
		mini->input = NULL;
		return (2);
	}
	return (0);
}

int	parser(t_shell *mini, t_env *env_dup)
{
	int	status;

	(void)env_dup;
	mini->input = readline(BEGIN "minishell-1.0$ " CLOSE);
	if (!mini->input)
	{
		status = *get_exit_status();
		silent_exit(mini, status);
	}
	if (mini->input[0] != '\0')
		add_history(mini->input);
	if (mini->input[0] == '\0')
	{
		free(mini->input);
		mini->input = NULL;
		return (0);
	}
	validate_input(mini);
	free(mini->input);
	mini->input = NULL;
	return (0);
}
