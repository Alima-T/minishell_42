/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:01:06 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/06 19:29:46 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
// for perror
# include "./LIBFT/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
// for for getenv, setenv
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
// for chdir, getcwd
# include <unistd.h>
// for PATH_MAX
# include <limits.h>
// for bool type
# include <stdbool.h>
# include <termios.h>

# define CLOSE "\001\033[0m\002"
// close (escape) any applied text formatting
# define BOLD "\001\033[1m\002" // bold formatting
# define BEGIN(x, y) "\001\033[" #x ";" #y "m\002"
// apply both x: background y : foreground colors to the text.

typedef struct s_builtin_cmd
{
	char					*cmd;
	struct s_builtin_cmd	*next;
}							t_builtin_cmd;

typedef struct s_shell
{
	char					*input;
	int						input_fd;
	int						output_fd;
	struct s_env			*env_dup;
	struct s_arg			*args;
	struct s_cmd			*cmds;
	t_builtin_cmd			*builtin_cmds;
}							t_shell;

typedef struct s_env
{
	char					*line;
	char					*key;
	char					*value;
	struct s_env			*next;
}							t_env;

typedef struct s_arg
{
	char					*arg_val;
	int						redir_flag;
	struct s_arg			*next;
}							t_arg;

typedef struct s_cmd
{
	char					**cmd;
	int						inp;
	int						out;
	int						pipe_fd[2];
	int						fork;
	pid_t					pid;
	struct s_redir			*redir;
	struct s_cmd			*next;
}							t_cmd;

typedef struct s_redir
{
	char					*type;
	char					*name;
	struct s_redir			*next;
}							t_redir;

/*** #ALIMA start # ***/

/*** BIG_UTILS  ***/
/***  args_handle.c  ***/
void						del_first_node(t_arg **args);
void						del_one(t_arg *lst);
void						list_destroy(t_arg **lst);
void						add_arg_end(t_arg **lst, t_arg *new);
t_arg						*new_arg(char *arg_str, t_shell *mini);

/* env_handle.c */
void						env_del_node(t_env *list);
void						env_destroy(t_env **list);
char						*find_in_env(t_env *env_dup, char *key);
int							env_dup_size(t_env *env_dup);
void						change_val_in_env_dup(t_env *env_dup, char *key,
								char *val);

/* cmds_handle.c */
void						redir_del_node(t_redir *redir_node);
void						redir_destroy(t_redir **redir_list);
void						cmd_del_node(t_cmd *cmd_node);
void						cmd_destroy(t_cmd **list);

/* mem_utils.c */
void						init(t_shell *mini);
void						*mem_allocator(size_t size);
void						free_shell_mem(t_shell *mini);

/* level_change.c */
void						shell_level_down(t_shell *shell_context);
void						shell_level_up(t_shell *shell_context);

/*** PARSING  */
/***  args_process.c ***/
int							find_end(char *input, int pos, int *flag);
int							is_redir(char *arg);
void						mark_redirect(t_arg *args);
void						split_input(char *input, t_arg **args,
								t_shell *mini);
t_arg						*process_args(t_shell *mini);
/*** cmds_create    ***/
int							find_cmd(t_arg *args);
char						**turn_cmd_to_array(t_arg *args, int lists_count);
t_cmd						*create_cmds_list(t_arg *args);
void						add_cmd_lst_end(t_cmd **list, t_cmd *new);

/*** cmds_process.c ***/
t_cmd						*process_cmds(t_shell *mini);
/***  dollar_process.c ***/
char						*replace_env_var(char *input, int start, int end,
								t_env *env_dup);
char						is_valid_char(char c);
char						*find_in_env(t_env *env_dup, char *key);
char						*question_handle(char *input, int begin, int *i);
char						*is_dollar(char *input, int *i, t_env *env_dup);
/***  envp_prosess.c ***/
char						*copy_value(char *env_part);
char						*copy_key(char *env_part);
void						envl_lstadd_back(t_env **list, t_env *new);
t_env						*envl_lstnew(char *env_str);
t_env						*copy_envp(char **envp);
/***  pars_special_chars.c ***/
char						*parse_special_chars(char *input, t_env *env_dup);
/*** parse_utils.c    ***/
int							skip_space_tab(char *inp, int i);
int							open_fd(char *path, char flag);
void						set_redir(t_cmd *cmds);
/***  parser.c     ***/
void						parser(t_shell *mini, t_env *env_dup);
/***  quotes_process.c  ***/
char						*combine_subs(char *input, int start, int end);
char						*is_quote(char *input, int *i);
char						*is_double_quote(char *input, int *i,
								t_env *env_dup);
/*** PRINTING  ***/
/* print_msgs.c*/
int							print_msg(int return_val, char *message,
								int exit_stat);
/*** VALIDATION ***/
/*** validator.c ***/
int							start_check(char *input, int i);
int							count_pipe_delim(char *input, int i);
int							count_quote(char *input, int *i, char quote);
int							finish_check(char *input, int *i);
int							validator(char *input);
/*** validate_redir.c ***/
int							redir_reading(char *input, int *i);
int							redir_writing(char *input, int *i);
int							redir_counting(char *input, int *i, char redir);
/*** redirect_process.c  ***/
int							redir_first(t_arg **args, t_redir **rdr);
void						redir_add_end(t_redir **list, t_redir *new);
t_redir						*redirect_process(t_arg **args);
t_redir						*redir_new(char *type, char *name);

/*** # ALIMA end # ***/

/*** # TANJA start # ***/

// builtins

int							builtin_cd(int ac, char *av[]);
int							builtin_echo(char **args);
int							builtin_pwd(void);
int							builtin_export(int ac, char *av[], char **env);
int							builtin_unset(int ac, char *av[], char ***env);
int							builtin_env(char **env);
int							builtin_exit(int ac, char *av[]);

// builtins utils

int							is_valid_var_name(const char *name);
size_t						ft_strcspn(const char *s, const char *reject);

// execution

void						execute_cmd(t_shell *mini);
int							execute_multiple_cmds(t_shell *mini);
int							execute_single_cmd_with_redir(t_cmd *cmd,
								t_shell *mini);
int							execute_builtin(t_cmd *cmd, t_shell *mini);
int							execute_external_cmd(t_cmd *cmd, t_shell *mini);

// execution helper

t_builtin_cmd				*init_builtin_cmds(void);
int							count_args(char **args);
int							is_builtin(const char *cmd, t_builtin_cmd *builtin_cmds);
char						**env_list_to_array(t_env *env_dup);
char						*find_executable(char *cmd);

// execution cleanup

void						free_builtin_cmds(t_builtin_cmd *builtin_cmds);
void						free_env_array(char **envp);
void						free_split(char **split);

// fake_global

int							*get_exit_status(void);

// handle_signals.c

void						sig_interact_ctrl_c(int signal);
void						sigs_interact_shell(void);
void						sig_non_interact_quit(int signal);
void						sig_non_interact_ctrl_c(int signal);
void						sigs_non_interact_shell(void);

/*** # TANJA end # ***/
#endif