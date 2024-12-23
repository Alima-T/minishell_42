/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:45:29 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/23 13:46:19 by aokhapki         ###   ########.fr       */
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
			return (env_dup->value);
		env_dup = env_dup->next;
	}
	return (NULL);
}