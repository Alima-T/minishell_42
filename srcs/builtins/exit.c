/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:17:26 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/21 19:46:41 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_with_error(t_shell *mini, char *arg, char *msg, int status)
{
	ft_putstr_fd(BEGIN "minishell: " CLOSE "exit: ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(msg, STDERR_FILENO);
	free_shell_mem_enhanced(mini);
	env_destroy(&mini->env_dup);
	free(mini);
	*get_exit_status() = status;
	exit(status);
}

static void	handle_exit_no_args(t_shell *mini)
{
	int	exit_status;

	exit_status = *get_exit_status();
	free_shell_mem_enhanced(mini);
	env_destroy(&mini->env_dup);
	free(mini);
	exit(exit_status);
}

static unsigned char	str_to_exit_code(t_shell *mini, char *str)
{
	int				i;
	int				sign;
	long long int	result;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * 10 + (str[i] - '0');
		else
			handle_non_digit(mini, str);
		i++;
	}
	return ((unsigned char)((result * sign) % 256));
}

static void	perform_exit(t_shell *mini, int exit_status)
{
	free_shell_mem_enhanced(mini);
	env_destroy(&mini->env_dup);
	free(mini);
	exit(exit_status);
}

int	builtin_exit(int ac, char *av[], t_shell *mini)
{
	int	exit_status;
	int	original_stdout;

	original_stdout = dup(STDOUT_FILENO);
	ft_putstr_fd("exit\n", original_stdout);
	close(original_stdout);
	if (ac == 1)
		handle_exit_no_args(mini);
	if (ac > 2)
	{
		ft_putstr_fd(BEGIN "minishell: " CLOSE "exit: too many arguments\n",
			STDERR_FILENO);
		return (1);
	}
	if (!is_numeric_str(av[1]))
		exit_with_error(mini, av[1], "numeric argument required", 255);
	exit_status = str_to_exit_code(mini, av[1]);
	perform_exit(mini, exit_status);
	return (exit_status);
}
