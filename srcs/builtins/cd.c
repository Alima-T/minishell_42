/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:17:00 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/17 18:40:25 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Handles errors in the cd command
 *
 * @param message Error message to display
 * @return int 1 to indicate error
 */
static int	cd_error(char *message)
{
	ft_putendl_fd(message, STDERR_FILENO);
	return (1);
}

/**
 * @brief Handles path-specific errors in the cd command
 *
 * @param path Path that caused the error
 * @return int 1 to indicate error
 */
static int	cd_path_error(char *path)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return (1);
}

/**
 * @brief Gets the target directory based on arguments
 *
 * @param ac Number of arguments
 * @param av Array of arguments
 * @param env_dup Environment variables
 * @return char* Target directory or NULL if error
 */
static char	*get_target_dir(int ac, char *av[], t_env **env_dup)
{
	char	*target_dir;

	if (ac == 1 || (av[1] && ft_strcmp(av[1], "~") == 0))
	{
		target_dir = find_in_env(*env_dup, "HOME");
		if (!target_dir)
			return (NULL);
	}
	else if (ft_strcmp(av[1], "-") == 0)
	{
		target_dir = find_in_env(*env_dup, "OLDPWD");
		if (!target_dir)
			return (NULL);
		ft_putendl_fd(target_dir, STDOUT_FILENO);
	}
	else
		target_dir = av[1];
	return (target_dir);
}

/**
 * @brief This function handles various cases like changing directory to home,
 * previous directory, or a specific path, while maintaining environment
 * variables.
 *
 * - cwd - buffer to store the current working directory path
 *
 * - target_dir - the target directory to change to
 *
 * @param ac number of command-line arguments
 * @param av array of strings containing the arguments
 * @param env_dup pointer to the environment variables list
 *
 * @return int 0 on success, 1 on error
 */
int	builtin_cd(int ac, char *av[], t_env **env_dup)
{
	char	cwd[PATH_MAX];
	char	*target_dir;

	if (ac > 2)
		return (cd_error("cd: too many arguments"));
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (cd_error(strerror(errno)));
	target_dir = get_target_dir(ac, av, *env_dup);
	if (!target_dir && (ac == 1 || !ft_strcmp(av[1], "~")))
		return (cd_error("cd: HOME not set"));
	else if (!target_dir && !ft_strcmp(av[1], "-"))
		return (cd_error("cd: OLDPWD not set"));
	update_env(*env_dup, "OLDPWD", cwd);
	if (chdir(target_dir))
		return (cd_path_error(target_dir));
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (cd_error(strerror(errno)));
	update_env(*env_dup, "PWD", cwd);
	return (0);
}
