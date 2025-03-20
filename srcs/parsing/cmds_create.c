/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:23:55 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/20 12:49:33 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Converts a linked list of arguments into an array of strings.
 * Allocates memory for the array and duplicates each argument string.
 * @param args A pointer to the linked list of arguments.
 * @param lists_count The number of arguments to convert.
 * @return A pointer to the created array of strings
 */
char	**turn_cmd_to_array(t_arg *args, int lists_count)
{
	char	**args_array;
	int		i;

	i = 0;
	args_array = (char **)malloc(sizeof(char *) * (lists_count + 1));
	if (!args_array)
		return (NULL);
	while (args && (lists_count != 0))
	{
		args_array[i] = ft_strdup(args->arg_val);
		i++;
		lists_count--;
		args = args->next;
	}
	args_array[i] = NULL;
	return (args_array);
}

/**
 * Finds the position of the command in the linked list of arguments.
 * Counts the number of arguments until a pipe character is found.
 * @param args A pointer to the linked list of arguments.
 * @return The position of the command or 0 if a pipe is found.
 */
int	find_cmd(t_arg *args)
{
	t_arg	*tmp;
	int		count;

	if (!args)
		return (0);
	tmp = args;
	count = 1;
	if (ft_strcmp("|", tmp->arg_val) == 0)
		return (0);
	while (tmp->next)
	{
		tmp = tmp->next;
		if (ft_strcmp(tmp->arg_val, "|") == 0)
			return (count);
		count++;
	}
	return (count);
}

/**
 * Creates a command structure from the linked list of arguments.
 * Allocates memory for the command structure and initializes its fields.
 * @param args A pointer to the linked list of arguments.
 * int lists_count; // Number of arguments in the linked list
 * t_cmd *cmd; // Pointer to the command structure
 * @return A pointer to the created command structure or NULL if allocation
 * fails.
 */
t_cmd	*create_cmds_lst(t_arg *args)
{
	int		lists_count;
	t_cmd	*cmd;

	cmd = (t_cmd *) malloc(sizeof(t_cmd));
	if (!cmd || !args)
		return (NULL);
	cmd->redir = NULL;
	cmd->redir = (struct s_redir *) redirect_process(&args);
	lists_count = find_cmd(args);
	cmd->cmd = turn_cmd_to_array(args, lists_count);
	cmd->orig_args = args;
	cmd->inp = 0;
	cmd->out = 1;
	cmd->fork = 0;
	cmd->pipe_fd[0] = 0;
	cmd->pipe_fd[1] = 0;
	cmd->next = NULL;
	return (cmd);
}
