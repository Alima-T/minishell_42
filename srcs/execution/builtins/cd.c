/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:17:00 by tbolsako          #+#    #+#             */
/*   Updated: 2024/12/19 14:12:21 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// determines the path to change to based on user input
static char	*get_cd_path(int ac, char *av[])
{
	char	*home;
	char	*oldpwd;
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
