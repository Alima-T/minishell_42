/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:01:06 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/20 15:12:11 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./LIBFT/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
// for perror
# include <stdio.h>
// for for getenv, setenv
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/wait.h>
// for chdir, getcwd
# include <unistd.h>
// for PATH_MAX
# include <limits.h>
// for bool type
# include <stdbool.h>

# define CLOSE "\001\033[0m\002" // close (escape) any applied text formatting
# define BOLD "\001\033[1m\002" // bold formatting
# define BEGIN(x, y) "\001\033[" #x ";" #y "m\002" // apply both x: background y : foreground colors to the text.

/* g_  global / ext_  external /stats
- status: stores the exit status of the last executed external command or process
*/
// ONLY ONE GLOBAL VAR 
int					g_ext_stats;

typedef struct s_shell
{
	char			*input;
	struct s_env	*env_copy;
	struct s_arg	*args;
	struct s_cmd	*cmds;
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
}					t_arg;

typedef struct s_cmd
{
	char			**command;
	int				inp;
	int				out;
	int				pipe_fd[2];
	int				fork;
	pid_t			pid;
	struct s_redir	*redir;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_redir
{
	char			*type;
	char			*name;
	struct s_redir	*next;
}					t_redir;

/*** #ALIMA start # ***/

/*** utils ***/
int					skip_space_tab(char *inp, int i);
int					open_fd(char *path, char flag);
void				set_redir(t_cmd *cmds);
int					print_msg(int return_val, char *message, int ext_stat);

/***  pars_special_chars.c alima ***/
char				*parse_special_chars(char *input, t_env *env_dup);

/***  args_process.c ***/
int					find_end(char *input, int pos, int *flag);
void				split_input(char *input, t_arg **args, t_shell *mini);
int					is_redir(char *arg);
void				mark_redirect(t_arg *args);
t_arg				*process_args(t_shell *minishell);

/***  args_handle.c  ***/
void				add_arg_end(t_arg **lst, t_arg *new);
t_arg				*new_arg(char *arg_str, t_shell *mini);
void				del_first_node(t_arg **args);
void				del_one(t_arg *lst);
void				list_destroy(t_arg **lst);

/***  quotes_process.c  ***/
char				*combine_subs(char *input, int start, int end);
char				*is_quote(char *input, int *i);
char				*is_double_quote(char *input, int *i, t_env *env_dup);

/***  dollar_process.c ***/
char				*replace_env_var(char *input, int start, int end, t_env *env_dup);
char				is_valid_char(char c);
char				*find_in_env(t_env *env_dup, char *key);
char				*ft_strjoin_connect(char const *s1, char *connect, char const *s2);
char				*question_handle(char *input, int begin, int *i);
char				*is_dollar(char *input, int *i, t_env *env_dup);

/*** cmds_create ***/
int					find_cmd(t_arg *args);
char				**turn_cmd_to_array(t_arg *args, int lists_count);
t_cmd				*create_cmds_list(t_arg *args);

t_redir				*redirect_process(t_arg **args);



/*** # ALIMA end # ***/

/*** # TANJA start # ***/

int					skip_space_tab(char *inp, int i);
int					open_fd(char *path, char flag);
void				set_redir(t_cmd *cmds);
int					find_end(char *input, int pos, int *flag);
void				split_input(char *input, t_arg **args, t_shell *minishell);
t_arg				*process_args(t_shell *minishell);

// builtins

int					builtin_cd(int ac, char *av[]);
void				builtin_echo(char **args);
void				builtin_pwd(void);
void				builtin_export(void);
void				builtin_unset(char **args);
void				builtin_env(void);
void				builtin_exit(void);

// utils

/*** # TANJA end # ***/
#endif