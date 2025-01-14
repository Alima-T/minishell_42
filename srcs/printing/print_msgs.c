/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:28:37 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/14 18:15:03 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	print_msg(int return_val, char *msg, int exit_stat)
{
	// Print a formatted prefix "[minishell ]$ " to stderr
	// BEGIN(49, 32) and CLOSE could be macros that add color or
	// special formatting.
	// 49: Default background color (terminal's default background).
	// 32: Green text color (foreground).
	ft_putstr_fd(BEGIN(49, 32) "minishell$ " CLOSE, STDERR_FILENO);
	// Print the provided message to stderr
	ft_putendl_fd(msg, STDERR_FILENO);
	*get_exit_status() = exit_stat;
	// Return the value of return_val
	// This value is typically used to signal success or failure to the caller.
	return (return_val);
}

void	print_args(t_arg *args)
{
	if (args == NULL)
		return ;
	while (args)
	{
		printf("args origin - |%s| \t %d\n", args->arg_val, args->redir_flag);
		args = args->next;
	}
}

void	error_msg(char *message)
{
	if (message)
		ft_putendl_fd(message, STDERR_FILENO);
	else
		perror("Error");
	*get_exit_status() = 128;
}

void	no_such_message(char *message)
{
	ft_putstr_fd(BEGIN(49, 32) "minishell$ " CLOSE, STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void	print_redir(t_cmd *cmds)
{
	t_redir	*temp;

	if (cmds == NULL)
		return ;
	while (cmds)
	{
		temp = (t_redir *)cmds->redir;
		if (temp == NULL)
			break ;
		while (temp)
		{
			printf("redirect type - |%s| \t name - |%s|\n", temp->type,
				temp->name);
			temp = temp->next;
		}
		cmds = cmds->next;
	}
}

void	print_cmds(t_cmd *cmds)
{
	int		i;
	t_redir	*temp;

	if (cmds == NULL || !cmds->cmd)
		return ;
	while (cmds)
	{
		i = 0;
		while (cmds->cmd[i])
		{
			printf("cmds command[%d] - |%s|\t input - |%d|\t output - |%d|\n",
				i, cmds->cmd[i], cmds->inp, cmds->out);
			i++;
		}
		temp = (t_redir *)cmds->redir;
		while (temp)
		{
			printf("redirect type - |%s| \t name - |%s|\n", temp->type,
				temp->name);
			temp = temp->next;
		}
		cmds = cmds->next;
	}
}

void	print_env_dup(t_env *env_dup)
{
	if (env_dup == NULL)
		return ;
	while (env_dup)
	{
		printf("%s\n", env_dup->line);
		printf("%s=%s\n", env_dup->key, env_dup->value);
		env_dup = env_dup->next;
	}
}
