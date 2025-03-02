/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:32:40 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/02 17:50:22 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Checks if the given argument is a redirection operator.
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
 * @param args A pointer to the list of arguments.
 */
void	set_redirect(t_arg *args)
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
/*
int *fl:
Указатель на целое число, которое будет обновлено для указания условий анализа:
0: По умолчанию, никаких особых условий не обнаружено.
1: Одно перенаправление ( <, |, >).
2: Двойное перенаправление (например, <<или >>).
*/
int	find_boundary(char *input, int pos, int *fl)
{
	char	quote;

	while (input[pos])
	{
		if (input[pos] == '\'' || input[pos] == '\"') // проверяет наличие ', " 
		{
			quote = input[pos]; // Переменная quote устанавливается на текущий символ кавычки (' или ").
			pos++; // Увеличивается pos, чтобы выйти за пределы открывающей кавычки.
			while (input[pos] != '\0' && input[pos] != quote) //move pos до тех пор, пока не найдет закрывающую кавычку или конец строки.
				pos++;
				//Это гарантирует, что заключенные в кавычки подстроки будут рассматриваться как единое целое, 
				//даже если они содержат специальные символы, такие как пробелы или символы перенаправления ( <, >, |).
			pos++; // added
			return pos; // added
		}
		if (ft_strchr(" \t<|>", input[pos])) //check if current char is a space or tab or redirect( <, >) or pipe (|) .
		{
			if (ft_strchr("<|>", input[pos])) //If the char is (<, >, or |) *fl = 1: The fl is set to 1, indicating a single redir or pipe.
				*fl = 1;
			if (ft_strchr("<>", input[pos]) && ft_strchr("<>", input[pos + 1])) //Double redir (<< or >>) If the current char is < or > and the next charis also < or >: *fl = 2: The fl is set to 2, indicating a double redir.
				*fl = 2;
			return (pos);
		}
		pos++;
	}
	return (pos);
}

/**
 * Splits the input string into arguments and handles special operators.
 * @param input The input string to be split.
 * @param args A double pointer to the list of arguments.
 * int	fl; - special handling for operators or redirs
 * @param mini A pointer to the shell structure.
 */
void	tokenize_input(char *input, t_arg **args, t_shell *mini)
{
	int		i;
	int		start;
	int		end;
	int		fl;
	char	*tmp;
	
	i = 0;
	fl = 0;
	while (input[i] != '\0')
	{
		i = skip_space_tab(input, i);
		start = i;						// Set the starting index of the current token
		if (input[i] == '\0')			// If the end of the string is reached, exit
			return ;
		end = find_boundary(input, i, &fl);	// Find the end of the current token or operator
		printf("flage is: %d\n", fl); //TO DO delete
		i = end;							// Move the index to the end of the current token
		// i = skip_space_tab(input, i);		// Skip trailing whitespaces (ensures clean arguments)
		if (fl != 0)						// If a special operator (<, <<, |, etc.) was detected
		{
			tmp = ft_substr(input, start, end - start);	// Extract the current token
			if (ft_strcmp(tmp, "\0"))					// Check if the token is non-empty
				append_arg(args, new_arg(tmp, mini)); // Add it to the args list
			else
				free(tmp);
			append_arg(args, new_arg(ft_substr(input, end, fl), mini)); // Add the special operator as a separate argument
			i += fl;		// Skip the special operator's length
			fl = 0;		// Reset the flag
		}
		else // If no special operator was detected
			append_arg(args, new_arg(ft_substr(input, start, end - start), mini));// Add the token to the args list
	}
}

/**
 * Processes the arguments from the shell structure.
 * Splits the input string into arguments and marks redirection flags.
 * @param mini A pointer to the shell structure containing input and arguments.
 * @return A pointer to the list of processed arguments.
 */
t_arg	*args_process(t_shell *mini)
{
	tokenize_input(mini->input, &(mini->args), mini);
	set_redirect(mini->args);
	return (mini->args);
}
