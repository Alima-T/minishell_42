/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:17:00 by tbolsako          #+#    #+#             */
/*   Updated: 2024/12/19 16:17:17 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

// retrieves the value of an env variable
static char	*get_env_var(const char *var_name)
{
	char	**env;
	int		i;
	size_t	len;

	env = *env_vars();
	i = 0;
	len = ft_strlen(var_name);
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

// updates an env variable and handles error reporting
static int	upd_env_var(const char *var_name, const char *value)
{
	if (add_or_upd_env(var_name, value) != 0)
	{
		ft_putendl_fd("cd: failed to upd env variable", 2);
		return (1);
	}
	return (0);
}

// checks if PWD and OLDPWD are set
static void	handle_missing_env_vars(void)
{
	char	cwd[PATH_MAX];

	if (!get_env_var("PWD") && getcwd(cwd, sizeof(cwd)) != NULL)
		upd_env_var("PWD", cwd);
	if (!get_env_var("OLDPWD") && getcwd(cwd, sizeof(cwd)) != NULL)
		upd_env_var("OLDPWD", cwd);
}

// determines the path to change to based on user input
static char	*get_cd_path(int ac, char *av[])
{
	char	*home;
	char	*oldpwd;

	home = get_env_var("HOME");
	if (ac == 1 || (ac == 2 && ft_strcmp(av[1], "~") == 0))
	{
		if (!home)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return (NULL);
		}
		return (home);
	}
	if (ac == 2 && ft_strcmp(av[1], "-") == 0)
	{
		oldpwd = get_env_var("OLDPWD");
		if (!oldpwd)
		{
			ft_putendl_fd("cd: OLDPWD not set", 2);
			return (NULL);
		}
		ft_putendl_fd(oldpwd, STDOUT_FILENO);
		return (oldpwd);
	}
	return (av[1]);
}

// changes the current working dir to the specified path
int	builtin_cd(int ac, char *av[])
{
	char	*path;

	if (ac > 2) // too many args
		return (0);
	handle_missing_env_vars(); // ensure PWD and OLDPWD are set
	path = get_cd_path(av, ac);
	if (!path)
		return (1); // error in getting path
	if (chdir(path) != 0)
	{
		*exit_status() = 1; // set exit status
		perror("cd");
		return (1); // change dir failed
	}
	// upd OLDPWD
	if (upd_env_var("OLDPWD", get_env_var("PWD")) != 0)
		return (1);
	// upd PWD
	if (upd_env_var("PWD", getcwd(NULL, 0)) != 0)
		return (1);
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
