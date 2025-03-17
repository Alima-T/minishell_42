/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:47:06 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/17 18:47:24 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Handles validation and error reporting for invalid variable names
 *
 * @param name Variable name to validate
 * @param arg Original argument for error reporting
 * @return int 0 if valid, 1 if invalid
 */
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

/**
 * @brief Checks if a key exists in the environment variables list
 *
 * @param env_dup Pointer to environment list
 * @param key Key to check
 * @return int 1 if the key exists, 0 otherwise
 */
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

/**
 * @brief Processes an append operation
 *
 * @param env_dup Environment list
 * @param arg_copy Argument copy
 * @param pos Position of "+="
 * @param arg Original argument
 * @return int 0 on success, 1 on error
 */
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

/**
 * @brief Processes and handles standard variable assignment
 *
 * Validates the variable name, aplits the argument at the equals sign,
 * and updates or creates the variable with the specified value.
 *
 * @param env_dup Environment list
 * @param arg_copy Argument copy to modify
 * @param pos Position of "="
 * @param arg Original argument for error reporting
 * @return int 0 on success, 1 on error
 */
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

/**
 * @brief Processes and handles variable with no assignment
 *
 * Validates the variablename and creates it with an empty value
 * if it doesn't already exist
 *
 * @param env_dup Environment list
 * @param name Variable name to validate
 * @param orig_arg Original argument for error reporting
 * @return int 0 on success, 1 on error
 */
int	process_no_value(t_env **env_dup, char *name, char *orig_arg)
{
	if (validate_and_report(name, orig_arg))
		return (1);
	if (!is_key_exist(env_dup, name))
		append_env(env_dup, new_env_with_value(name, ""));
	return (0);
}
