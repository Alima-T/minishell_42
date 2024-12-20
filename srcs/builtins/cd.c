/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:17:00 by tbolsako          #+#    #+#             */
/*   Updated: 2024/12/20 17:53:56 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// retrieves the value of an env variable
static char	*get_env_var(const char *var_name)
{
	// char	**env;
	// int		i;
	// size_t	len;
	// env = *env_vars();
	// i = 0;
	// len = ft_strlen(var_name);
	// while (env[i])
	// {
	// 	if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
	// 		return (env[i] + len + 1);
	// 	i++;
	// }
	return (getenv(var_name));
}

// checks if PWD and OLDPWD are set
static void	handle_missing_env_vars(void)
{
	char	cwd[PATH_MAX];

	if (!get_env_var("PWD") && getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (setenv("PWD", cwd, 1) != 0)
			perror("cd: failed to upd env variable");
	}
	if (!get_env_var("OLDPWD") && getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (setenv("OLDPWD", cwd, 1) != 0)
			perror("cd: failed to upd env variable");
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

	if (ac > 2) // too many args
		return (0);
	handle_missing_env_vars(); // ensure PWD and OLDPWD are set
	path = get_cd_path(ac, av);
	if (!path)
		return (1); // error in getting path
	if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
	{
		perror("cd: getcwd");
		return (1); // failed to get current dir
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1); // change dir failed
	}
	// upd OLDPWD and PWD
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (setenv("OLDPWD", oldpwd, 1) != 0) // set OLDPWD to the previous PWD
			perror("cd: failed to upd env variable");
		if (setenv("PWD", cwd, 1) != 0)
			perror("cd: failed to upd env variable");
				// upd PWD to the current dir
	}
	else
		perror("cd");
	return (0);
}

// void	builtin_cd(char **args)
// {
// 	const char	*error_message;

// 	// checks if an arg is provided; if not, writes an error message to STDERR
// 	if (args[1] == NULL)
// 	{
// 		error_message = "cd: missing args\n";
// 		// 2 - STDERR_FILENO (file descriptor for standard error output)
// 		write(STDERR_FILENO, error_message, ft_strlen(error_message));
// 		return ;
// 	}
// 	// changes the current working dir; if it fails, it prints the error message
// 	if (chdir(args[1]) != 0)
// 		perror("cd"); // error reporting
// }
