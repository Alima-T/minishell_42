/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:32:40 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/20 15:12:11 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
/*
Summary of Functions:
1. find_end:
This function identifies the end position of a token in the input string, handling quoted strings and checking for redirection or pipe characters. It updates the flag to indicate if a special operator was found.
split_input:
This function splits the input string into individual arguments, handling special operators and whitespace. It uses find_end to determine the boundaries of each token and adds them to the argument list.
is_redir:
This function checks if a given argument is a redirection operator (e.g., >, >>, <, <<). It returns 1 if it is a redirection operator and 0 otherwise.
4. mark_redirect:
This function traverses the argument list and sets flags for redirection operators. It marks the operator with a redir_flag of 1 and the following argument with a redir_flag of 2.
5. process_args:
This function orchestrates the processing of arguments by calling split_input to parse the input string and mark_redirect to set the appropriate flags. It returns the list of processed arguments.
This code is part of a parser for a shell-like environment, responsible for interpreting command-line input, handling arguments, and managing redirection operators.
*/
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
			if (ft_strchr("<|>", input[pos])) //If the char is (<, >, or |) *flag = 1: The flag is set to 1, indicating a single redir or pipe.
				*flag = 1;
			if (ft_strchr("<>", input[pos]) && ft_strchr("<>", input[pos + 1])) //Double redir (<< or >>) If the current char is < or > and the next charis also < or >: *flag = 2: The flag is set to 2, indicating a double redir.
				*flag = 2;
			return (pos);
		}
		pos++;
	}
	return (pos);
}

/**
 * Splits the input string into arguments and handles special operators.
 *
 * @param input The input string to be split.
 * @param args A double pointer to the list of arguments.
 * @param mini A pointer to the shell structure.
 */
void	split_input(char *input, t_arg **args, t_shell *mini)
{
	int		i;
	int		start;						// beginning of the current argument
	int		end;						// end of the current argument
	int		flag;						// special handling for operators or redirs
	char	*tmp;						// temp storage for the current substring
	i = 0;
	flag = 0;
	while (input[i] != '\0')
	{
		i = skip_space_tab(input, i);	// Skip any leading whitespaces
		start = i;						// Set the starting index of the current token
		if (input[i] == '\0')			// If the end of the string is reached, exit
			return ;
		end = find_end(input, i, &flag);	// Find the end of the current token or operator
		i = end;							// Move the index to the end of the current token
		i = skip_space_tab(input, i);		// Skip trailing whitespaces (ensures clean arguments)
		if (flag != 0)						// If a special operator (<, <<, |, etc.) was detected
		{
			tmp = ft_substr(input, start, end - start);	// Extract the current token
			if (ft_strcmp(tmp, "\0"))					// Check if the token is non-empty
				add_arg_end(args, new_arg(tmp, mini)); // Add it to the args list
			else
				free(tmp);
			add_arg_end(args, new_arg(ft_substr(input, end, flag), mini)); // Add the special operator as a separate argument
				
			i += flag;		// Skip the special operator's length
			flag = 0;		// Reset the flag
		}
		else // If no special operator was detected
			add_arg_end(args, new_arg(ft_substr(input, start, end - start), mini));// Add the token to the args list
	}
}

/**
 * Checks if the given argument is a redirection operator.
 *
 * @param arg The argument string to check.
 * @return 1 if the argument is a redirection operator, 0 otherwise.
 */
int	is_redir(char *arg)
{
	if ((ft_strcmp(arg, ">") == 0)
		|| (ft_strcmp(arg, ">>") == 0)
		|| (ft_strcmp(arg, "<") == 0)
		|| (ft_strcmp(arg, "<<") == 0))
		return (1);
	return (0);
}


/**
 * Marks redirection flags in the argument list.
 * Sets the redir_flag for redirection operators and their following arguments.
 *
 * @param args A pointer to the list of arguments.
 */
void	mark_redirect(t_arg *args)
{
	while (args)
	{
		if (is_redir(args->arg_val) == 1)
		{
			args->redir_flag = 1;
			args->next->redir_flag = 2;
			args = args->next->next;
		}
		else if (args)
			args = args->next;
	}
}

/**
 * Processes the arguments from the shell structure.
 * Splits the input string into arguments and marks redirection flags.
 *
 * @param minishell A pointer to the shell structure containing input and arguments.
 * @return A pointer to the list of processed arguments.
 */
t_arg	*process_args(t_shell *minishell)
{
	split_input(minishell->input, &(minishell->args), minishell);
	mark_redirect(minishell->args);
	return (minishell->args);
}

