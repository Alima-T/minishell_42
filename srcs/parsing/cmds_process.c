/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:34:37 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/20 12:52:06 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Adds a new command structure to the end of the command list.
 * @param list A double pointer to the head of the command list.
 * @param new A pointer to the new command structure to be added.
 */
void	append_cmd(t_cmd **list, t_cmd *new)
{
	t_cmd	*last;

	if (!list || !new)
		exit(EXIT_FAILURE);
	if (*list)
	{
		last = *list;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	else
		*list = new;
}

/*process_cmds_and_redirs проходит по всем командам (cmd) и перенаправлениям
(rdr) в структуре данных оболочки 
и применяет функцию parse_special_chars к каждой строке команды и имени файла
перенаправления. 
Эта обработка выполняет разбор специальных символов, таких как кавычки (', ")
и переменные окружения ($), 
используя данные из mini->env_dup, которые содержат переменные окружения. 
В результате все команды и имена файлов очищаются и подготавливаются для
выполнения, разрешая или удаляя последовательности специальных символов.
*/
void	process_cmds_and_redirs(t_shell *mini)
{
	t_cmd	*cmd;
	t_redir	*rdr;
	int		i;

	cmd = mini->cmds;
	rdr = (t_redir *) mini->cmds->redir;
	while (cmd)
	{
		if (cmd->cmd)
		{
			i = 0;
			while (cmd->cmd[i])
			{
				cmd->cmd[i] = parse_special_chars(cmd->cmd[i], mini->env_dup);
				i++;
			}
		}
		while (rdr)
		{
			rdr->name = parse_special_chars(rdr->name, mini->env_dup);
			rdr = rdr->next;
		}
		cmd = cmd->next;
	}
}

/*
Summary of the Function:
t_arg	*tmp; // Temporary pointer to traverse the linked list of arguments
t_arg	*cmd_start; // Pointer to mark the beginning of a command
Purpose: The cmds_process function processes a linked list of arguments from a
shell structure (t_shell *mini) and creates a list of commands (t_cmd) based on
the presence of pipe characters (|).
Logic:
It first checks if there are any arguments. If not, it returns NULL.
It initializes pointers to traverse the argument list and to mark the beginning
of each command.
It loops through the arguments, checking for pipe characters. When a pipe is
found, it creates a command from the arguments collected so far and updates the
starting point for the next command.
After the loop, it ensures that the last segment of arguments is also processed
into a command.
Return Value: The function returns a linked list of commands created from the
input arguments.
*/
t_cmd	*cmds_process(t_shell *mini)
{
	t_arg	*tmp;
	t_arg	*cmd_start;

	if (mini->args == NULL)
		return (NULL);
	tmp = mini->args;
	cmd_start = tmp;
	if ((ft_strcmp(tmp->arg_val, "|")) == 0)
		tmp = tmp->next;
	while (tmp)
	{
		if ((ft_strcmp(tmp->arg_val, "|")) == 0)
		{
			append_cmd(&mini->cmds, create_cmds_lst(cmd_start));
			cmd_start = tmp->next;
		}
		tmp = tmp->next;
	}
	append_cmd(&mini->cmds, create_cmds_lst(cmd_start));
	process_cmds_and_redirs(mini);
	return (mini->cmds);
}
