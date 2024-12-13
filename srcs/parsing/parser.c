/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:51:57 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/13 19:42:39 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parser(t_shell *mini, t_env *env_dup)
{
	(void)env_dup;
	mini->input = readline(BEGIN(49, 32)"[minishell ]$ "CLOSE);
	if (!mini->input)
		exit(g_ext_stats);
	if (*mini->input)
		add_history (mini->input);
	if (validator(mini->input) == 0)
	{
		mini->args = process_args(mini);
		// mini->cmds = process_cmds(mini);
	}
	free(mini->input);
	mini->input = NULL;
}