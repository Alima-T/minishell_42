/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:44:56 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/17 18:46:00 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Creates a quoted value for an environment variable
 *
 * @param value Value to quote
 * @return char* Quoted value (must be freed by caller)
 */
static char	*create_quoted_value(char *value)
{
	char	*quoted_val;
	char	*result;

	quoted_val = ft_strjoin("\"", value);
	if (!quoted_val)
		return (NULL);
	result = ft_strjoin(quoted_val, "\"");
	free(quoted_val);
	return (result);
}

/**
 * @brief Creates a formatted string for an environment variable
 *
 * @param env_node Environment node to format
 * @return char* Formatted string (must be freed by caller)
 */
char	*format_env_var(t_env *env_node)
{
	char	*key_value;
	char	*quoted_val;
	char	*final;

	if (!env_node->val)
		return (ft_strdup(env_node->key));
	key_value = ft_strjoin(env_node->key, "=");
	if (!key_value)
		return (NULL);
	quoted_val = create_quoted_value(env_node->val);
	if (!quoted_val)
	{
		free(key_value);
		return (NULL);
	}
	final = ft_strjoin(key_value, quoted_val);
	free(key_value);
	free(quoted_val);
	return (final);
}

/**
 * @brief Prints and frees the sorted environment array
 *
 * @param sorted_env Array of sorted environment strings
 * @param count Number of variables
 */
void	print_sorted_env(char **sorted_env, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(sorted_env[i], STDOUT_FILENO);
		free(sorted_env[i]);
		i++;
	}
	free(sorted_env);
}

/**
 * @brief Updates environment variable by appending a value
 *
 * @param existing Existing environment variable to update
 * @param name Variable name
 * @param value Value to append
 */
static void	update_env_append(t_env *existing, char *name, char *value)
{
	char	*new_value;
	char	*new_line;

	if (existing->val)
	{
		new_value = ft_strjoin(existing->val, value);
		free(existing->val);
		existing->val = new_value;
	}
	else
		existing->val = ft_strdup(value);
	free(existing->line);
	new_line = ft_strjoin(name, "=");
	existing->line = ft_strjoin(new_line, existing->val);
	free(new_line);
}

/**
 * @brief Handles appending to an existing environment variable
 *
 * @param env_dup Environment list
 * @param name Variable name
 * @param value Value to append
 * @return int 0 on success
 */
int	handle_append_operation(t_env **env_dup, char *name, char *value)
{
	t_env	*existing;

	existing = *env_dup;
	while (existing)
	{
		if (ft_strcmp(existing->key, name) == 0)
		{
			update_env_append(existing, name, value);
			return (0);
		}
		existing = existing->next;
	}
	append_env(env_dup, new_env_with_value(name, value));
	return (0);
}
