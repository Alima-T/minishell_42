/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:45:29 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/23 14:27:45 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Summary of Functions:
1. copy_value:
This function duplicates the value part of an environment variable string (in the format KEY=VALUE). It returns the duplicated value or NULL if no value exists.
copy_key:
This function duplicates the key part of an environment variable string. It returns the duplicated key.
3. envl_lstnew:
This function creates a new environment variable node. It allocates memory for the node, duplicates the entire environment variable string, extracts the key and value, and initializes the node's fields.
4. envl_lstadd_back:
This function adds a new environment variable node to the end of a linked list. It checks if the list is empty and either sets the new node as the head or traverses to the end of the list and links the new node there.
copy_envp:
This function copies the environment variables from an array into a linked list. It iterates through the array, creating new nodes for each environment variable and adding them to the linked list.
This code is part of a system for managing environment variables in a shell-like environment, allowing for the storage and retrieval of key-value pairs representing environment settings. It ensures proper memory management and linked list operations for the environment variables.
*/

#include "../../minishell.h"

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
	{
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
