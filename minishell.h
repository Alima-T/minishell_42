/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:01:06 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/13 13:27:16 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./LIBFT/libft.h"

#define CLOSE		"\001\033[0m\002"			// close (escape) any applied text formatting
#define BOLD		"\001\033[1m\002"			// bold formatting
#define BEGIN(x,y)	"\001\033["#x";"#y"m\002"	// apply both bx: background, y: foreground colors to the text. 

/*
g_  global / ext_  external /stats - status 
global exit status or global external status, stores the exit status of the last executed external command or process
*/
int		g_ext_stats; 

typedef struct s_shell
{
	char			*input;
	struct s_envl	*env_copy;
	struct s_argl	*args;
	struct s_cmdl	*cmds;
}					t_shell;

typedef struct s_env
{
	char			*line;
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_arg
{
	char			*arg_val;
	int				redir_flag;
	struct s_arg	*next;
}				t_arg;

typedef struct s_cmd
{
	char			**command;
	int				in;
	int				out;
	int				pipe_fd[2];
	int				fork;
	pid_t			pid;
	struct s_rdr	*redir;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_redir
{
	char			*type;
	char			*name;
	struct s_redir	*next;
}				t_redir;

/*
 * utils alima
 */
int				skip_space_tab(char *inp, int i);
int				open_fd(char *path, char flag);
void			set_redirection(t_cmd *cmds);
int				find_end(char *input, int pos, int *flag);
void			split_input(char *input, t_arg **args, t_shell *minishell);
t_arg			*process_args(t_shell *minishell);

/*
 * utils tanja
 */

#endif