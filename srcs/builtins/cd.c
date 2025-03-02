/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:17:00 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/02 17:32:46 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Retrieves the value of an env variable.
 * @param var_name
 * @return
 */
static char	*get_env_var(const char *var_name)
{
	char	*value;

	value = getenv(var_name);
	if (!value)
		return (NULL);
	return (value);
}

/**
 * Updates environment variable in env_dup list
 */
static void	upd_env_var(t_env **env_dup, const char *key, const char *value)
{
	t_env	*tmp;
	char	*new_line;

	tmp = *env_dup;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->val);
			tmp->val = ft_strdup(value);
			new_line = ft_strjoin(key, "=");
			new_line = ft_strjoin(new_line, value);
			free(tmp->line);
			tmp->line = new_line;
			return ;
		}
		tmp = tmp->next;
	}
}

/**
 * Checks if PWD and OLDPWD are set.
 * @param env_dup
 */
static void	handle_missing_env_vars(t_env **env_dup)
{
	char	cwd[PATH_MAX];
	t_env	*tmp;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return ;
	tmp = *env_dup;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		upd_env_var(env_dup, "PWD", cwd);
	tmp = *env_dup;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		upd_env_var(env_dup, "OLDPWD", cwd);
}

/**
 * Determines the path to change to based on user input.
 * @param ac
 * @param av
 * @return
 */
static char	*get_cd_path(int ac, char *av[])
{
	char	*home;
	char	*oldpwd;

	home = get_env_var("HOME");
	if (ac == 1)
	{
		if (home == NULL)
		{
			write(STDERR_FILENO, "cd: HOME not set\n", 17);
			return (NULL);
		}
		return (home);
	}
	if (ac == 2)
	{
		if (ft_strcmp(av[1], "~") == 0)
		{
			if (home == NULL)
			{
				write(STDERR_FILENO, "cd: HOME not set\n", 17);
				return (NULL);
			}
			return (home);
		}
		if (ft_strcmp(av[1], "-") == 0)
		{
			oldpwd = get_env_var("OLDPWD");
			if (oldpwd == NULL)
			{
				write(STDERR_FILENO, "cd: OLDPWD not set\n", 20);
				return (NULL);
			}
			write(STDOUT_FILENO, oldpwd, ft_strlen(oldpwd));
			write(STDOUT_FILENO, "\n", 1);
			return (oldpwd);
		}
	}
	return (av[1]);
}

/**
 * Changes the current working directory to the specified path.
 * @param ac
 * @param av
 * @param env_dup
 * @return
 */
int	builtin_cd(int ac, char *av[], t_env **env_dup)
{
	char	*path;
	char	oldpwd[PATH_MAX];
	char	cwd[PATH_MAX];

	if (ac > 2)
	{
		write(STDERR_FILENO, "cd: too many arguments\n", 23);
		return (1);
	}
	handle_missing_env_vars(env_dup);
	path = get_cd_path(ac, av);
	if (!path)
		return (1);
	if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
	{
		perror("cd: getcwd");
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		upd_env_var(env_dup, "OLDPWD", oldpwd);
		upd_env_var(env_dup, "PWD", cwd);
	}
	else
		perror("cd");
	return (0);
}
