/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:32:40 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/12 19:53:29 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"
/*
int *flag:
Указатель на целое число, которое будет обновлено для указания условий анализа:
0: По умолчанию, никаких особых условий не обнаружено.
1: Одно перенаправление ( <, |, >).
2: Двойное перенаправление (например, <<или >>).
*/
int	find_end(char *input, int pos, int *flag)
{
	char	quote;

	while (input[pos])
	{
		if (input[pos] == '\'' || input[pos] == '\"') // блок проверяет наличие одинарных (') или двойных (") кавычек.
		{
			quote = input[pos]; // Переменная quote устанавливается на текущий символ кавычки (' или ").
			pos++; // Увеличивается pos, чтобы выйти за пределы открывающей кавычки.
			while (input[pos] != '\0' && input[pos] != quote) //move pos до тех пор, пока не найдет закрывающую кавычку или конец строки.
				pos++;
				//Это гарантирует, что заключенные в кавычки подстроки будут рассматриваться как единое целое, 
				//даже если они содержат специальные символы, такие как пробелы или символы перенаправления ( <, >, |).
		}
		if (ft_strchr(" \t<|>", input[pos])) //check if current char is a space or tab or redirect( <, >) or pipe (|) .
		{
			if (ft_strchr("<|>", input[pos])) //If the char is (<, >, or |) *flag = 1: The flag is set to 1, indicating a single redirection or pipe.
				*flag = 1;
			if (ft_strchr("<>", input[pos]) && ft_strchr("<>", input[pos + 1])) //Double Redirection (<< or >>) If the current char is < or > and the next charis also < or >: *flag = 2: The flag is set to 2, indicating a double redirection.
				*flag = 2;
//			pos = pass_whitespaces(input, pos);
			return (pos);
		}
		pos++;
	}
	return (pos);
}

void	split_input(char *input, t_arg **args, t_shell *minishell)
{
	int		i;
	int		begin;						// Marks the beginning of the current argument
	int		end;						// Marks the end of the current argument
	int		flag;						// Indicates special handling for operators or redirections
	char	*tmp;						// Temporary storage for the current substring
	i = 0;
	flag = 0;
	while (input[i] != '\0')
	{
		i = skip_space_tab(input, i);	// Skip any leading whitespaces
		begin = i;						// Set the starting index of the current token
		if (input[i] == '\0')			// If the end of the string is reached, exit
			return ;
		end = find_end(input, i, &flag);	// Find the end of the current token or operator
		i = end;							// Move the index to the end of the current token
		i = skip_space_tab(input, i);		// Skip trailing whitespaces (ensures clean arguments)
		if (flag != 0)						// If a special operator (<, <<, |, etc.) was detected
		{
			tmp = ft_substr(input, begin, end - begin);	// Extract the current token
			if (ft_strcmp(tmp, "\0"))					// Check if the token is non-empty
				add_arg_to_end(args, new_arg(tmp, minishell)); // Add it to the args list
			else
				free(tmp);                             // Free the empty token
			add_arg_to_end(args,                     // Add the special operator as a separate argument
				new_arg(ft_substr(input, end, flag), minishell));
			i += flag;                                 // Skip the special operator's length
			flag = 0;                                  // Reset the flag
		}
		else // If no special operator was detected
			add_arg_to_end(args, new_arg(ft_substr(input, begin, end - begin), minishell));// Add the token to the args list
	}
}

int	is_redirection(char *arg)
{
	if ((ft_strcmp(arg, ">") == 0)
		|| (ft_strcmp(arg, ">>") == 0)
		|| (ft_strcmp(arg, "<") == 0)
		|| (ft_strcmp(arg, "<<") == 0))
		return (1);
	return (0);
}

void	mark_redirect(t_arg *args)
{
	while (args)
	{
		if (is_redirection(args->arg_val) == 1)
		{
			args->redir_flag = 1;
			args->next->redir_flag = 2;
			args = args->next->next;
		}
		else if (args)
			args = args->next;
	}
}

t_arg	*process_args(t_shell *minishell)
{
	split_input(minishell->input, &(minishell->args), minishell);
	mark_redirect(minishell->args);
	return (minishell->args);
}

