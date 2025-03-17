/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:55:59 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/17 18:49:16 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Validates if a string is a valid shell variable name
 *
 * Checks that the variable name follows shell naming conventions:
 *
 * - Must not be NULL or empty
 *
 * - First character must be a letter or underscore
 *
 * - Remaining characters must be letters, digits, or underscores
 *
 * @param name String to validate as a variable name
 * @return int 1 if name is valid, 0 otherwise
 */
int	validate_var_name(const char *name)
{
	int	i;

	i = 0;
	if (!name || !*name)
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Creates a new environment variable with a key and value
 *
 * @param key Variable name
 * @param value Variable value
 * @return t_env* New environment node
 */
t_env	*new_env_with_value(char *key, char *value)
{
	t_env	*node;
	char	*temp;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->val = ft_strdup(value);
	temp = ft_strjoin(key, "=");
	node->line = ft_strjoin(temp, value);
	free(temp);
	node->next = NULL;
	return (node);
}
