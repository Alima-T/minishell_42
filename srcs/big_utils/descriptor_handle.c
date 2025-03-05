
#include "../../minishell.h"

/**
 * Input Redirection
 * Output Redirection
 */
int	setup_redirections(t_cmd *cmds)
{
	if (cmds->inp != STDIN_FILENO) //input is redirected from a file or a pipe.
	{
		if (dup2(cmds->inp, STDIN_FILENO) < 0) //duplicates cmds->inp to standard input (0).
			return (1);
		close(cmds->inp);
	}
	if (cmds->out != STDOUT_FILENO) //output is redirected to a file or a pipe.
	{
		if (dup2(cmds->out, STDOUT_FILENO) < 0) // duplicates cmds->out to standard output (1)
			return (1);
		close(cmds->out);
	}
	return (0);
}