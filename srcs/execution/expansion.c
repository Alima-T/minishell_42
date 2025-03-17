/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:53:38 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/17 18:54:05 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Gets the value of an environment variable
 * @param env_dup Environment linked list
 * @param name Variable name
 * @return Variable value or NULL if not found
 */
char	*get_env_var_value(t_env *env_dup, const char *name)
{
	while (env_dup)
	{
		if (ft_strcmp(env_dup->key, name) == 0)
			return (env_dup->val);
		env_dup = env_dup->next;
	}
	return (NULL);
}

/**
 * Expands environment variables in a string
 * @param str Input string
 * @param env_dup Environment variables
 * @return New string with expanded variables or NULL on error
 */
char	*expand_env_vars(char *str, t_env *env_dup)
{
	char	*result;
	char	*var;
	char	*value;
	char	*temp;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			if (str[i] == '?')
			{
				value = ft_itoa(*get_exit_status());
				if (!value)
				{
					free(result);
					return (NULL);
				}
				temp = ft_strjoin(result, value);
				free(result);
				free(value);
				if (!temp)
					return (NULL);
				result = temp;
				i++;
			}
			else if (ft_isalnum(str[i]) || str[i] == '_')
			{
				var = ft_strdup("");
				if (!var)
				{
					free(result);
					return (NULL);
				}
				while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				{
					temp = ft_strjoin_char(var, str[i]);
					free(var);
					if (!temp)
					{
						free(result);
						return (NULL);
					}
					var = temp;
					i++;
				}
				value = get_env_var_value(env_dup, var);
				if (value)
				{
					temp = ft_strjoin(result, value);
					free(result);
					if (!temp)
					{
						free(var);
						return (NULL);
					}
					result = temp;
				}
				free(var);
			}
			else
			{
				temp = ft_strjoin_char(result, '$');
				free(result);
				if (!temp)
					return (NULL);
				result = temp;
			}
		}
		else
		{
			temp = ft_strjoin_char(result, str[i]);
			free(result);
			if (!temp)
				return (NULL);
			result = temp;
			i++;
		}
	}
	return (result);
}
