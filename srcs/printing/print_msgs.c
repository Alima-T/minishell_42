/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alima <alima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:28:37 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/04 22:19:48 by alima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	print_msg(int ret_val, char *message, int ext_stat)
{
	ft_putstr_fd(BEGIN"msh-1.0$ "CLOSE, STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	*get_exit_status() = ext_stat;
	return (ret_val);
}

void	print_cmds(t_cmd *cmds)
{
	int		i;
	t_redir	*tmp;

	if (cmds == NULL || !cmds->cmd)
		return ;
	while (cmds)
	{
		i = 0;
		while (cmds->cmd[i])
		{
			printf("cmd[%d] - |%s|\t input - |%d|\t output - |%d|\n", \
					i, cmds->cmd[i], cmds->inp, cmds->out);
			i++;
		}
		tmp = (t_redir *) cmds->redir;
		while (tmp)
		{
			printf("redirect - |%s| \t name - |%s|\n", tmp->type, tmp->name);
			tmp = tmp->next;
		}
		cmds = cmds->next;
	}
}

void	print_args(t_arg *args)
{
	if (args == NULL)
		return ;
	while (args)
	{
		printf("original args - |%s| \t %d\n", args->arg_val, args->redir_flag);
		args = args->next;
	}
}

void	print_env_copy(t_env *env_dup)
{
	if (env_dup == NULL)
		return ;
	while (env_dup)
	{
		printf("%s\n", env_dup->line);
		printf("%s=%s\n", env_dup->key, env_dup->val);
		env_dup = env_dup->next;
	}
}

void	print_redir(t_cmd *cmds)
{
	t_redir	*tmp;

	if (cmds == NULL)
		return ;
	while (cmds)
	{
		tmp = (t_redir *) cmds->redir;
		if (tmp == NULL)
			break ;
		while (tmp)
		{
			printf("redirect type - |%s| \t name - |%s|\n", tmp->type, tmp->name);
			tmp = tmp->next;
		}
		cmds = cmds->next;
	}
}


