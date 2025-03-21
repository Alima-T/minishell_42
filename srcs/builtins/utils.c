/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:55:59 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/21 16:58:00 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
