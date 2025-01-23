/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:09:43 by tbolsako          #+#    #+#             */
/*   Updated: 2025/01/23 18:14:20 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Expands environment variables.
 * @param str
 * @return
 */
char	*expand_env_vars(char *str)
{
	char	*result;
	char	*var;
	char	*value;
	char	*temp;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '?')
			{
				value = ft_itoa(*get_exit_status());
				temp = ft_strjoin(result, value);
				free(result);
				result = temp;
				free(value);
				i++;
			}
			else
			{
				var = ft_strdup("");
				while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				{
					temp = ft_strjoin_char(var, str[i]);
					free(var);
					var = temp;
					i++;
				}
				value = getenv(var);
				if (value)
				{
					temp = ft_strjoin(result, value);
					free(result);
					result = temp;
				}
				free(var);
			}
		}
		else
		{
			temp = ft_strjoin_char(result, str[i]);
			free(result);
			result = temp;
			i++;
		}
	}
	return (result);
}
