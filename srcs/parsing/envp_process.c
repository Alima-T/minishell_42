/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:35:35 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/21 17:35:48 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*copy_value(char *env_part)
{
	int		i;
	char	*valdup;

	i = 0;
	while (env_part[i] != '=' && env_part[i] != '\0')
		i++;
	if (env_part[i] == '\0')
		valdup = NULL;
	else
		valdup = ft_strdup(&env_part[i + 1]);
	return (valdup);
}

static char	*copy_key(char *env_part)
{
	int		i;
	char	*keydup;

	i = 0;
	while (env_part[i] != '=' && env_part[i] != '\0')
		i++;
	keydup = ft_substr(env_part, 0, i);
	return (keydup);
}

t_env	*new_env(char *env_str)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->line = ft_strdup(env_str);
	node->key = copy_key(env_str);
	if (ft_strcmp(node->key, "OLDPWD") == 0)
		node->val = NULL;
	else
		node->val = copy_value(env_str);
	node->next = NULL;
	return (node);
}

void	append_env(t_env **list, t_env *new)
{
	t_env	*last;

	if (!list || !new)
		exit(EXIT_FAILURE);
	if (*list)
	{
		last = *list;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	else
		*list = new;
}

t_env	*copy_envp(char **envp)
{
	t_env	*envp_copy;
	int		i;

	i = 0;
	envp_copy = NULL;
	while (envp[i])
	{
		append_env(&envp_copy, new_env(envp[i]));
		i++;
	}
	return (envp_copy);
}
