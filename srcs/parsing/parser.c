/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:51:57 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/14 18:35:30 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// /**
//  * Validates the input string for the shell.
//  *
//  * @param input The input string to validate.
//  * @return 0 if the input is valid, -1 if invalid.
//  */

void	parser(t_shell *mini, t_env *env_dup)
{
	(void)env_dup;
	mini->input = readline(BEGIN(49, 32) "minishell$ " CLOSE);
	if (mini->input == NULL && *mini->input == '\0')
		exit(*get_exit_status());
	// {
	// 	if (mini->input == NULL && *mini->input == '\0')
	// 	{
	// 		printf("Exiting shell.\n");
	// 		exit(EXIT_SUCCESS); 
	// 	}
	// 	perror("Error reading input");
	// 	exit(EXIT_FAILURE);
	// }
	if (*mini->input)
		add_history(mini->input);
	if (validator(mini->input) == 0)
	{
		mini->args = process_args(mini);
		mini->cmds = process_cmds(mini);
		// execute_cmd(mini); // Call the function to execute the command
	}
	free(mini->input);
	mini->input = NULL;
}
