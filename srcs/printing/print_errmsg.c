
#include "../../minishell.h"

void	cmd_not_found_msg(char *message)
{
	ft_putstr_fd(BEGIN"msh-1.0$ "CLOSE, STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("command not found\n", STDERR_FILENO);
}

void	errmsg(char *message)
{
	if (message)
		ft_putendl_fd(message, STDERR_FILENO);
	else
		perror("Error");
	*get_exit_status() = 128;
}