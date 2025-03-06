/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:51:57 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/06 18:39:02 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// /**
//  * Validates the input string for the shell.
//  * @param input The input string to validate.
//  * @return 0 if the input is valid, -1 if invalid.
//  */
void	parser(t_shell *mini, t_env *env_dup)
{
	(void)env_dup;
	mini->input = readline(BEGIN "msh-1.0$ "CLOSE);
	if (!mini->input)
	{
		printf("exit\n");
		exit(*get_exit_status());
	}
	if (*mini->input)
		add_history (mini->input);
	if (validator(mini->input) == 0)
	{
		mini->args = args_process(mini);
		mini->cmds = cmds_process(mini);
	}
	free(mini->input);
	mini->input = NULL;
}
