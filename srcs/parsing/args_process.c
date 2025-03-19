/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:32:40 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/19 12:07:49 by tbolsako         ###   ########.fr       */
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
		if (input[pos] == '\'' || input[pos] == '\"')
		{
			quote = input[pos]; // Переменная quote устанавливается на текущий символ кавычки (' или ").
			pos++; // Увеличивается pos, чтобы выйти за пределы открывающей кавычки.
			while (input[pos] && input[pos] != quote) //move pos до тех пор, пока не найдет закрывающую кавычку или конец строки.
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
// void	lex_input(char *input, t_arg **args, t_shell *mini)
// {
// 	int		i;
// 	int		start;
// 	int		end;
// 	int		fl;
// 	char	*tmp;
// 	// int		i_old;
// 	// bool	has_space;
// 	// t_arg	*new_node;

// 	i = 0;
// 	fl = 0;
// 	while (input[i] != '\0')
// 	{
// 		// i_old = i;
// 		i = skip_space_tab(input, i);
// 		// if (i_old != i)
// 		// 	has_space = true;
// 		// else
// 		// 	has_space = false;
// 		// Set the starting index of the current token
// 		start = i;
// 		// If the end of the string is reached, exit
// 		if (input[i] == '\0')
// 			return ;
// 		// Find the end of the current token or operator
// 		end = find_boundary(input, i, &fl);
// 		// printf("flage is: %d\n", fl); //TO DO delete
// 		// Move the index to the end of the current token
// 		i = end;
// 		// i = skip_space_tab(input, i);
// 		// Skip trailing whitespaces (ensures clean arguments)
// 		// If a special operator (<, <<, |, etc.) was detected
// 		if (fl != 0)
// 		{
// 			// Extract the current token
// 			tmp = ft_substr(input, start, end - start);
// 			// Check if the token is non-empty
// 			if (ft_strcmp(tmp, "\0"))
// 				append_arg(args, new_arg(tmp, mini)); // Add it to the args list
// 			else
// 				free(tmp);
			
// 			// Add the special operator as a separate argument
// 			append_arg(args, new_arg(ft_substr(input, end, fl), mini));
// 			// Skip the special operator's length
// 			i += fl;
// 			// Reset the flag
// 			fl = 0;
// 		}
// 		// If no special operator was detected
// 		else
// 			append_arg(args, new_arg(ft_substr(input, start, end - start), mini)); // Add the token to the args list
// 	}
// }
void	lex_input(char *input, t_arg **args, t_shell *mini)
{
	int		i;
	int		start;
	int		end;
	int		fl;
	char	*tmp;
	int		i_old;
	bool	has_space;
	t_arg	*new_node;

	i = 0;
	fl = 0;
	while (input[i] != '\0')
	{
		i_old = i;
		i = skip_space_tab(input, i);
		if (i_old != i)
			has_space = true;
		else
			has_space = false;
		// Set the starting index of the current token
		start = i;
		// If the end of the string is reached, exit
		if (input[i] == '\0')
			return ;
		// Find the end of the current token or operator
		end = find_boundary(input, i, &fl);
		// printf("flage is: %d\n", fl); //TO DO delete
		// Move the index to the end of the current token
		i = end;
		// i = skip_space_tab(input, i);
		// Skip trailing whitespaces (ensures clean arguments)
		// If a special operator (<, <<, |, etc.) was detected
		if (fl != 0)
        {
            // For token before separator
            tmp = ft_substr(input, start, end - start);
            if (ft_strcmp(tmp, "\0"))
            {
                new_node = new_arg(tmp, mini);
                new_node->space_flag_arg = has_space;
                append_arg(args, new_node);
            }
            else
                free(tmp);
            
            // For separator token
            new_node = new_arg(ft_substr(input, end, fl), mini);
            new_node->space_flag_arg = false;  // Normally no space after separators
            append_arg(args, new_node);
            
            i += fl;
            fl = 0;
        }
        else
        {
            new_node = new_arg(ft_substr(input, start, end - start), mini);
            new_node->space_flag_arg = has_space;
            append_arg(args, new_node);
        }
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
	lex_input(mini->input, &(mini->args), mini);
	set_redirect(mini->args);
	return (mini->args);
}
