/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:23:55 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/21 17:29:41 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**turn_cmd_to_array(t_arg *args, int lists_count)
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

static int	find_cmd(t_arg *args)
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
