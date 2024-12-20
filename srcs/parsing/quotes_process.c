/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:45:29 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/20 18:19:58 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Concatenates three strings into a new dynamically allocated string.
 *
 * @param s1 The first string to concatenate.
 * @param s2 The second string to concatenate.
 * @param s3 The third string to concatenate.

	* @return A pointer to the newly allocated string containing the concatenated result,
 *         or NULL if allocation fails.
 */
char	*ft_strjoin_con(const char *s1, const char *s2, const char *s3)
{
	size_t	len1;
	size_t	len2;
	size_t	len3;
	size_t	total_length;
	char	*result;
	char	*ptr;

	// Calculate the lengths of the strings
	if (s1 != NULL)
		len1 = ft_strlen(s1);
	else
		len1 = 0;
	if (s2 != NULL)
		len2 = ft_strlen(s2);
	else
		len2 = 0;
	if (s3 != NULL)
		len3 = ft_strlen(s3);
	else
		len3 = 0;
	// Calculate total length for the new string
	total_length = len1 + len2 + len3;
	// Allocate memory for the new string (+1 for the null terminator)
	result = (char *)malloc(total_length + 1);
	if (result == NULL)
		return (NULL); // Return NULL if allocation fails
	// Copy the strings into the new string
	ptr = result;
	if (s1 != NULL)
	{
		ft_memcpy(ptr, s1, len1);
		ptr += len1;
	}
	if (s2 != NULL)
	{
		ft_memcpy(ptr, s2, len2);
		ptr += len2;
	}
	if (s3 != NULL)
	{
		ft_memcpy(ptr, s3, len3);
		ptr += len3;
	}
	// Null-terminate the new string
	result[total_length] = '\0';
	return (result); // Return the concatenated string
}

/**

	* function processes a substring of the input string by extracting parts before,
 * between,
	and after specified indices (start and end). It frees the original input
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
 * within the quotes,
	updating the iterator as it finds these characters. It calls

	* combine_subs to handle the substring between the opening and closing double quotes.
 *
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
	{
		if (input[*i] == '$')
			// Check for dollar sign for variable substitution.
			input = is_dollar(input, i, env_dup);
		if (input[*i] == '\"') // Check for the closing double quote.
			break ;
	}
	input = combine_subs(input, start, *i);
		// Call combine_subs to process the substring.
	return (input);                         // Return the modified input string.
}
