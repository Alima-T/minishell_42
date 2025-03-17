/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:50:16 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/17 18:51:09 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Counts the number of arguments in a command.
 * @param args
 * @return
 */
static int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

/**
 * Checks if a command is a built-in command.
 * @param cmd
 * @param builtin_cmds
 * @return
 */
int	is_builtin(const char *cmd, t_builtin_cmd *builtin_cmds)
{
	t_builtin_cmd	*current;

	current = builtin_cmds;
	while (current)
	{
		if (ft_strcmp(cmd, current->cmd) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

static int	dispatch_builtin(int ac, char *av[], t_shell *mini)
{
	if (ft_strcmp(av[0], "cd") == 0)
		return (builtin_cd(ac, av, &mini->env_dup));
	else if (ft_strcmp(av[0], "echo") == 0)
		return (builtin_echo(av));
	else if (ft_strcmp(av[0], "env") == 0)
		return (builtin_env(mini->env_dup));
	else if (ft_strcmp(av[0], "exit") == 0)
		return (builtin_exit(ac, av, mini));
	else if (ft_strcmp(av[0], "export") == 0)
		return (builtin_export(ac, av, mini->env_dup));
	else if (ft_strcmp(av[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(av[0], "unset") == 0)
		return (builtin_unset(ac, av, &mini->env_dup));
	return (1);
}

/**
 * Initializes the linked list of built-in commands.
 * @param
 * @return
 */
t_builtin_cmd	*init_builtin_cmds(void)
{
	t_builtin_cmd	*head;
	t_builtin_cmd	*new_node;
	int				i;
	const char		*cmds[] = {"cd", "echo", "env", "exit", "export", "pwd", \
								"unset", NULL};

	head = NULL;
	i = 0;
	while (cmds[i] != NULL)
	{
		new_node = (t_builtin_cmd *)malloc(sizeof(t_builtin_cmd));
		if (!new_node)
			return (NULL);
		new_node->cmd = ft_strdup(cmds[i]);
		new_node->next = head;
		head = new_node;
		i++;
	}
	return (head);
}

/**
 * Executes a built-in command.
 * @param cmd
 * @param mini
 * @return
 */
int	execute_builtin(t_cmd *cmd, t_shell *mini)
{
	t_builtin_cmd	*current;
	int				cmd_count;

	cmd_count = count_args(cmd->cmd);
	current = mini->builtin_cmds;
	while (current)
	{
		if (ft_strcmp(cmd->cmd[0], current->cmd) == 0)
		{
			*get_exit_status() = dispatch_builtin(cmd_count, cmd->cmd, mini);
			return (0);
		}
		current = current->next;
	}
	return (1);
}
