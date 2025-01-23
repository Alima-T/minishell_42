/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:17:00 by tbolsako          #+#    #+#             */
/*   Updated: 2025/01/23 14:55:11 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// retrieves the value of an env variable
static char	*get_env_var(const char *var_name)
{
	return (getenv(var_name));
}

// checks if PWD and OLDPWD are set
static void	handle_missing_env_vars(void)
{
	char	cwd[PATH_MAX];

	if (!get_env_var("PWD") && getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (setenv("PWD", cwd, 1) != 0)
			perror("cd: failed to update env variable");
	}
	if (!get_env_var("OLDPWD") && getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (setenv("OLDPWD", cwd, 1) != 0)
			perror("cd: failed to update env variable");
	}
}

// determines the path to change to based on user input
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

// changes the current working dir to the specified path
int	builtin_cd(int ac, char *av[])
{
	char	*path;
	char	oldpwd[PATH_MAX];
	char	cwd[PATH_MAX];

	// too many args
	if (ac > 2)
	{
		write(STDERR_FILENO, "cd: too many arguments\n", 23);
		return (1);
	}
	// ensure PWD and OLDPWD are set
	handle_missing_env_vars();
	path = get_cd_path(ac, av);
	if (!path)
	{
		// error in getting path
		return (1);
	}
	if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
	{
		perror("cd: getcwd");
		// failed to get current dir
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		// change dir failed
		return (1);
	}
	// upd OLDPWD and PWD
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		// set OLDPWD to the previous PWD
		if (setenv("OLDPWD", oldpwd, 1) != 0)
			perror("cd: failed to upd env variable");
		// upd PWD to the current dir
		if (setenv("PWD", cwd, 1) != 0)
			perror("cd: failed to upd env variable");
	}
	else
		perror("cd");
	return (0);
}
