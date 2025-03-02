/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:45:29 by aokhapki          #+#    #+#             */
/*   Updated: 2025/02/25 19:20:27 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

// char *gap(char *str, int i)
// {
// 	int j = i;
// 	char *tmp;
// 	char *tmp2;
// 	char *tmp3;
	
// 	while(str[++i])
// 		if(str[i] == '\'')
// 			break;
// 	tmp = ft_substr(str, 0, j-1);
// 	tmp = ft_substr(str, j + 1, i - j - 1);
// 	tmp3 = ft_strdup(str + j + 1);
// 	tmp = ft_strjoin(tmp, tmp2);
// 	tmp = ft_strjoin(tmp, tmp3);
// 	printf("tmp = %s\n", tmp);
// 	free(str);
// 	return(tmp);
// }

// void pars(char *str)
// {
// 	int i;
// 	i = -1;
// 	while(str[++i])
// 	{
// 		if(str[i] == '\'')
// 			gap(str, i);
// 	}
// }

/* my code*/
/**
 * function processes a substring of the input string by extracting parts before,
 * between,  and after specified indices (start and end). It frees the original input
 * and returns a new str that combines the extracted parts.
 *
 * @param input The original input string.
 * @param start The starting index of the substring to be processed.
 * @param end The ending index of the substring to be processed.
 * @return The newly combined string after processing.
 */
char	*combine_subs(char *input, int start, int end)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp1 = ft_substr(input, 0, start);                  
		// Part before the start index
	tmp2 = ft_substr(input, start + 1, end - start - 1);
		// Part between start and end
	tmp3 = ft_strdup(input + end + 1);                  
		// Part after the end index
	free(input);                                        
		// Free the original input string to avoid memory leaks.
	input = NULL;
	input = ft_strjoin_con(tmp1, tmp2, tmp3);
		// Combine the three parts into a new string.
	free(tmp1);
	free(tmp2);
	free(tmp3);
	return (input); // Return the newly combined string.
}

/**
 * function processes single quotes in the input. It finds the position
 * of the closing single quote and calls combine_subs to handle the substring
 * between the opening and closing quotes.
 *
 * @param input The original input string.
 * @param i A pointer to the current index in the input string.
 * @return The modified input string after processing single quotes.
 */
char	*is_quote(char *input, int *i)
{
	int	start;

	start = *i;           // Store the starting index of the quote.
	while (input[++(*i)]) // Increment the index until a closing quote is found.
	{
		if (input[*i] == '\'') // Check for the closing single quote.
			break ;
	}
	input = combine_subs(input, start, *i);
		// Call combine_subs to process the substring.
	return (input);                         // modified input string.
}

/**
 * function processes double quotes in the input string. It handles dollar signs
 * within the quotes, updating the iterator as it finds these characters. 
 * It calls * combine_subs to handle the substring between the opening and closing double quotes.
 * @param input The original input string.
 * @param i A pointer to the current index in the input string.
 * @param env_dup A pointer to the environment variables (used for variable expansion).
 * @return The modified input string after processing double quotes.
 */
char	*is_double_quote(char *input, int *i, t_env *env_dup)
{
	int	start;

	start = *i; // Store the starting index of the double quote.
	while (input[++(*i)])
		// Increment the index until a closing double quote is found.
	{		/* в двойных кавычках отрабатывает \, если после него идет ", $ или \ */
		if (input[*i] == '\\' && (input[*i + 1] == '\"' \
				|| input[*i + 1] == '$' || input[*i + 1] == '\\'))
			input = is_slash(input, i);
		if (input[*i] == '$')
			// Check for dollar sign for variable substitution.
			input = is_dollar(input, i, env_dup);
		if (input[*i] == '\"') // Check for the closing double quote.
			break ;
	}
	input = combine_subs(input, start, *i);
		// Call combine_subs to process the substring.
	return (input);  // Return the modified input string.
}
