/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:34:37 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/09 17:06:57 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Parses special characters in the input string, handling quotes, escape characters,
 * and variable expansions.
 * 
 * @param input The original input string to be parsed.
 * @param env_dup A pointer to the environment variables (used for variable expansion).
 * @return The modified input string after processing special characters.
 */
// "", '', $, |, $?, <, >, <<, >>

char	*parse_special_chars(char *input, t_env *env_dup)
{
	int i;
	i = 0;
	while(input[i])
	{
		if(input[i] == '\'')
			input = is_quote(input, &i);
		if(input[i] == '\"')
			input = is_double_quote(input, &i, env_dup);
		if(input[i] == '$')
			input = is_dollar(input, &i, env_dup);
		i++;
	}
	return (input);
}

/*process_cmds_and_redirs проходит по всем командам (cmd) и перенаправлениям (rdr) в структуре данных оболочки 
и применяет функцию parse_special_chars к каждой строке команды и имени файла перенаправления. 
Эта обработка выполняет разбор специальных символов, таких как кавычки (', ") и переменные окружения ($), 
используя данные из mini->env_dup, которые содержат переменные окружения. 
В результате все команды и имена файлов очищаются и подготавливаются для выполнения, 
разрешая или удаляя последовательности специальных символов.
*/

void process_cmds_and_redirs(t_shell *mini)
{
	t_cmd *cmd;
	t_redir *rdr;
	int i;
	
	cmd = mini->cmds;
	rdr = (t_redir *) mini->cmds->redir;
	while(cmd)
	{
		if(cmd->cmd)
		{
			i = 0;
			while(cmd->cmd[i])
			{
				cmd->cmd[i] = parse_special_chars(cmd->cmd[i], mini->env_dup);
				i++;
			}
		}
		while(rdr)
		{
			rdr->name = parse_special_chars(rdr->name, mini->env_dup);
			rdr = rdr->next;
		}
		cmd = cmd->next;
	}
}

/*
Summary of the Function:
Purpose: The process_cmds function processes a linked list of arguments from a shell structure (t_shell *mini) and creates a list of commands (t_cmd) based on the presence of pipe characters (|).
Logic:
It first checks if there are any arguments. If not, it returns NULL.
It initializes pointers to traverse the argument list and to mark the beginning of each command.
It loops through the arguments, checking for pipe characters. When a pipe is found, it creates a command from the arguments collected so far and updates the starting point for the next command.
After the loop, it ensures that the last segment of arguments is also processed into a command.
Return Value: The function returns a linked list of commands created from the input arguments.
*/

t_cmd	*process_cmds(t_shell *mini)
{
	t_arg	*tmp; // Temporary pointer to traverse the linked list of arguments
	t_arg	*cmd_begin; // Pointer to mark the beginning of a command
	// Check if the argument list is empty; if so, return NULL
	if (mini->args == NULL)
		return (NULL); // Return NULL if there are no arguments
	tmp = mini->args; // Initialize the temporary pointer to the head of the argument list
	cmd_begin = tmp; // Set the command beginning pointer to the current argument
	// Check if the first argument is a pipe; if so, move to the next argument
	if ((ft_strcmp(tmp->arg_val, "|")) == 0)
		tmp = tmp->next; // Move to the next argument if the first is a pipe
	// Loop through the argument list to process commands
	while (tmp)
	{
		// Check if the current argument is a pipe
		if ((ft_strcmp(tmp->arg_val, "|")) == 0)
		{
			// If a pipe is found, create a command from the arguments collected so far
			add_cmd_lst_end(&mini->cmds, create_cmds_list(cmd_begin));
			cmd_begin = tmp->next; // Update the command beginning pointer to the next argument
		}
		tmp = tmp->next; // Move to the next argument in the list
	}
	// After the loop, create a command for the last segment of arguments
	add_cmd_lst_end(&mini->cmds, create_cmds_list(cmd_begin));
	process_cmds_and_redirs(mini);
	return (mini->cmds); // Return the list of commands created
}