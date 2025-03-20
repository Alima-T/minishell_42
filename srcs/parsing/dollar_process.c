/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:47:13 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/20 12:56:53 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
Summary of the Function:
Purpose: The cmds_process function processes a linked list of arguments from a
shell structure (t_shell *mini) and creates a list of commands (t_cmd) based on
the presence of pipe characters (|).
Logic:
It first checks if there are any arguments. If not, it returns NULL.
It initializes pointers to traverse the argument list and to mark the beginning
of each command.
It loops through the arguments,
	checking for pipe characters. When a pipe is found,
	it creates a command from the arguments collected so far and updates the
	starting point for the next command.
After the loop,
	it ensures that the last segment of arguments is also processed into a
	command.
Return Value: The function returns a linked list of commands created from the
input arguments.
*/
// Replaces an environment variable in the input string with its corresponding
// value.
// It extracts the key from the input, retrieves its value from the environment,
// and constructs a new string with the substituted value.
char	*replace_env(char *input, int start, int end, t_env *env_dup)
{
	char	*result;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*key;

	tmp1 = ft_substr(input, 0, start);
	if (input[start + 1] == '{' && input[end - 1] == '}')
		key = ft_substr(input, start + 2, end - start - 3);
	else
		key = ft_substr(input, start + 1, end - start - 1);
	tmp2 = find_in_env(env_dup, key);
	if (tmp2)
		tmp2 = ft_strdup(tmp2);
	else
		tmp2 = ft_strdup("");
	tmp3 = ft_strdup(input + end);
	result = ft_strjoin_con(tmp1, tmp2, tmp3);
	free(tmp1);
	free(tmp2);
	free(tmp3);
	free(key);
	free(input);
	return (result);
}

// This function handles the case when a question mark is encountered in the
// input string.
// It retrieves the current value of g_ext_stats,
// constructs a new string with this value,
// and resets g_ext_stats to 0.
char	*question_handle(char *input, int start, int *i)
{
	char	*line_new;
	char	*tmp_1;
	char	*tmp_2;
	char	*nbr_val;
	char	*tail;

	nbr_val = ft_itoa(*get_exit_status());
	tmp_1 = ft_substr(input, 0, start);
	tmp_2 = ft_strjoin(tmp_1, nbr_val);
	tail = ft_strdup(&input[*i]);
	line_new = ft_strjoin(tmp_2, tail);
	free(nbr_val);
	free(tmp_1);
	free(tmp_2);
	free(tail);
	free(input);
	return (line_new);
}

// If a char is a valid (underscore or alphanumeric). Returns 0 - if not valid
char	is_valid_char(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

// Check for dollar in the input string and determines if they represent
// an environment variable or a special case ("?"). Updates the iterator
// and calls the appropriate handler function to process the input.
char	*is_dollar(char *input, int *i, t_env *env_dup)
{
	int	start;
	int	key_start;
	int	key_end;

	start = *i;
	if (ft_strchr("?", input[start + 1]))
	{
		*i += 2;
		return (question_handle(input, start, i));
	}
	if (input[start + 1] == '{')
	{
		(*i)++;
		while (input[++(*i)])
		{
			if (input[*i] == '}')
			{
				(*i)++;
				break ;
			}
			if (!is_valid_char(input[*i]) && input[*i] != '}')
				return (input);
		}
		if (input[*i - 1] != '}')
			return (input);
		key_start = start + 2;
		key_end = *i - 1;
		if (key_end <= key_start)
			return (input);
		return (replace_env(input, start, *i, env_dup));
	}
	while (input[++(*i)])
	{
		if (!is_valid_char(input[*i]))
			break ;
	}
	if (*i == start + 1)
		return (input);
	input = replace_env(input, start, *i, env_dup);
	return (input);
}
