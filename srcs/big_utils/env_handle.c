/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:45:29 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/21 16:55:03 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_in_env(t_env *env_dup, char *key)
{
	if (!env_dup || !key)
		return (NULL);
	while (env_dup)
	{
		if (!ft_strcmp(env_dup->key, key))
			return (env_dup->val);
		env_dup = env_dup->next;
	}
	return (NULL);
}

int	count_env_vars(t_env *env_dup)
{
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = env_dup;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

static void	update_existing_env(t_env *current, char *key, char *val)
{
	if (current->val)
		free(current->val);
	current->val = ft_strdup(val);
	if (current->line)
		free(current->line);
	current->line = ft_strjoin_con(key, "=", val);
}

void	update_env(t_env *env_dup, char *key, char *val)
{
	t_env	*current;
	t_env	*new_node;
	char	*new_var;

	if (!env_dup || !key || !val)
		return ;
	current = env_dup;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			update_existing_env(current, key, val);
			return ;
		}
		current = current->next;
	}
	new_var = ft_strjoin_con(key, "=", val);
	new_node = new_env(new_var);
	free(new_var);
	if (new_node)
		append_env(&env_dup, new_node);
}

void	env_del_node(t_env *list)
{
	if (!list)
		return ;
	free(list->line);
	list->line = NULL;
	free(list->key);
	list->key = NULL;
	free(list->val);
	list->val = NULL;
	free(list);
	list = NULL;
}
