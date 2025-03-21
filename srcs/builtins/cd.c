/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:17:00 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/21 16:56:01 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	cd_error(char *message)
{
	ft_putstr_fd(BEGIN "minishell: " CLOSE, STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	return (1);
}

static int	cd_path_error(char *path)
{
	ft_putstr_fd(BEGIN "minishell: " CLOSE, STDERR_FILENO);
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return (1);
}

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
		if (ft_strncmp(target_dir, "OLDPWD=", 7) == 0)
			target_dir += 7;
		ft_putendl_fd(target_dir, STDOUT_FILENO);
	}
	else
		target_dir = av[1];
	return (target_dir);
}

int	builtin_cd(int ac, char *av[], t_env **env_dup)
{
	char	cwd[PATH_MAX];
	char	*target_dir;

	if (ac > 2)
		return (cd_error("cd: too many arguments"));
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (cd_error(strerror(errno)));
	target_dir = get_target_dir(ac, av, env_dup);
	if (!target_dir && (ac == 1 || !ft_strcmp(av[1], "~")))
		return (cd_error("cd: HOME not set"));
	else if (!target_dir && !ft_strcmp(av[1], "-"))
		return (cd_error("cd: OLDPWD not set"));
	if (chdir(target_dir) == -1)
		return (cd_path_error(target_dir));
	update_env(*env_dup, "OLDPWD", cwd);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (cd_error(strerror(errno)));
	update_env(*env_dup, "PWD", cwd);
	return (0);
}
