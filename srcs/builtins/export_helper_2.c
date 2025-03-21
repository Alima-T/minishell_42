/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:47:06 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/21 16:57:15 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	validate_and_report(char *name, char *arg)
{
	if (!validate_var_name(name))
	{
		ft_putstr_fd("export: '", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (1);
	}
	return (0);
}

static int	is_key_exist(t_env **env_dup, char *key)
{
	t_env	*tmp;

	tmp = *env_dup;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	process_append(t_env **env_dup, char *arg_copy, char *pos, char *arg)
{
	char	*name;
	char	*value;

	*pos = '\0';
	name = arg_copy;
	value = pos + 2;
	if (validate_and_report(name, arg))
		return (1);
	return (handle_append_operation(env_dup, name, value));
}

int	process_assignment(t_env **env_dup, char *arg_copy, char *pos, char *arg)
{
	char	*name;
	char	*value;

	*pos = '\0';
	name = arg_copy;
	value = pos + 1;
	if (validate_and_report(name, arg))
		return (1);
	if (is_key_exist(env_dup, name))
		update_env(*env_dup, name, value);
	else
		append_env(env_dup, new_env_with_value(name, value));
	return (0);
}

int	process_no_value(t_env **env_dup, char *name, char *orig_arg)
{
	if (validate_and_report(name, orig_arg))
		return (1);
	if (!is_key_exist(env_dup, name))
		append_env(env_dup, new_env_with_value(name, ""));
	return (0);
}
