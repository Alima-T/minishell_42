/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:01:06 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/21 17:49:28 by tbolsako         ###   ########.fr       */
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
# ifdef __unix__
#  include <termios.h>
# endif
# define CLOSE "\001\033[0m\002"
# define BOLD "\001\033[1m\002"
# define BEGIN "\001\033[1;32;40m\002"

typedef struct s_num
{
	int						i;
	int						start;
	int						end;
	int						i_old;
	int						fl;
	bool					has_space;
}							t_num;

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
	struct s_num			nums;
	t_builtin_cmd			*builtin_cmds;
}							t_shell;

typedef struct s_env
{
	char					*line;
	char					*key;
	char					*val;
	struct s_env			*next;
}							t_env;

typedef struct s_arg
{
	char					*arg_val;
	int						redir_flag;
	bool					space_flag_arg;
	struct s_arg			*next;
}							t_arg;

typedef struct s_redir
{
	char					*type;
	char					*name;
	struct s_redir			*next;
}							t_redir;

typedef struct s_cmd
{
	char					**cmd;
	int						inp;
	int						out;
	int						pipe_fd[2];
	int						fork;
	pid_t					pid;
	t_arg					*orig_args;
	struct s_redir			*redir;
	struct s_cmd			*next;
}							t_cmd;

/*** BIG_UTILS  ***/
/*** args_handle.c ***/
void						del_first_node(t_arg **args);
void						arglst_destroy(t_arg **lst);
void						append_arg(t_arg **lst, t_arg *new);
t_arg						*new_arg(char *arg_str, t_shell *mini);

/*** cmds_handle.c ***/
void						cmdlst_destroy(t_cmd **list);

/*** fd_and_heredoc_handle.c ***/
int							open_helper(char *path, char flag);
char						*generate_heredoc_filename(void);

/*** env_handle.c ***/
void						update_env(t_env *env_dup, char *key, char *val);
char						*find_in_env(t_env *env_dup, char *key);
int							count_env_vars(t_env *env_dup);
void						env_del_node(t_env *list);

/*** level_change.c ***/
void						shell_level_down(t_shell *mini);
void						shell_level_up(t_shell *mini);

/*** mem_mngt.c ***/
void						cleanup_cmd(t_cmd *cmd);
void						env_destroy(t_env **list);

/*** mem_utils.c ***/
void						*mem_allocator(size_t size);
void						free_array(char **array);
void						free_builtin_cmds(t_builtin_cmd *builtin_cmds);
void						free_shell_mem_enhanced(t_shell *mini);

/*** PARSING ***/
/*** args_process.c ***/
t_arg						*args_process(t_shell *mini);

/*** args_utils.c ***/
void						set_redirect(t_arg *args);

/*** cmds_create ***/
t_cmd						*create_cmds_lst(t_arg *args);

/*** cmds_process.c ***/
t_cmd						*cmds_process(t_shell *mini);

/*** dollar_process.c ***/
char						*is_dollar(char *input, int *i, t_env *env_dup);

/*** envp_process.c ***/
void						append_env(t_env **list, t_env *new);
t_env						*new_env(char *env_str);
t_env						*copy_envp(char **envp);

/*** parse_special_chars.c ***/
char						*parse_special_chars(char *input, t_env *env_dup);

/*** parse_utils.c ***/
char						*is_slash(char *input, int *i);
bool						is_token_separator(char c);
int							skip_space_tab(char *inp, int i);

/*** parser.c ***/
int							parser(t_shell *mini, t_env *env_dup);

/*** quotes_process.c ***/
char						*combine_subs(char *input, int start, int end);
char						*is_quote(char *input, int *i);
char						*is_db_quote(char *input, int *i, t_env *env_dup);

/*** redirect_process.c ***/
t_redir						*redirect_process(t_arg **args);

/*** VALIDATION ***/
/*** validator.c ***/
int							validator(char *input);

/*** validate_redir.c ***/
int							redir_counting(char *input, int *i, char redir);

/*** validate_quote.c ***/
int							count_pipe_delim(char *input, int i);
int							count_quote(char *input, int *i, char quote);

/*** PRINTING  ***/
/*** print_msgs.c ***/
int							print_msg(int return_val, char *msg, int exit_stat);

/*** SIGNALS ***/
/*** handle_signals.c ***/
void						sig_interact_ctrl_c(int signal);
void						sigs_interact_shell(void);
void						sig_non_interact_quit(int signal);
void						sig_non_interact_ctrl_c(int signal);
void						sigs_non_interact_shell(void);

/*** BUILT-INS ***/
/*** cd.c ***/
int							builtin_cd(int ac, char *av[], t_env **env_dup);

/*** echo.c ***/
int							builtin_echo(char **args, t_arg *orig_args);

/*** env.c ***/
int							builtin_env(t_env *env_dup);

/*** exit.c ***/
int							builtin_exit(int ac, char *av[], t_shell *mini);
void						exit_with_error(t_shell *mini, char *arg, char *msg,
								int status);

/*** exit_helper.c ***/
int							is_numeric_str(char *str);
void						handle_non_digit(t_shell *mini, char *str);
void						silent_exit(t_shell *mini, int status);

/*** export.c ***/
int							builtin_export(int ac, char *av[], t_env *env_dup);

/*** export_helper_1.c ***/
char						*format_env_var(t_env *env_node);
void						print_sorted_env(char **sorted_env, int count);
int							handle_append_operation(t_env **env_dup, char *name,
								char *value);

/*** export_helper_2.c ***/
int							process_append(t_env **env_dup, char *arg_copy,
								char *pos, char *arg);
int							process_assignment(t_env **env_dup, char *arg_copy,
								char *pos, char *arg);
int							process_no_value(t_env **env_dup, char *name,
								char *orig_arg);

/*** pwd.c ***/
int							builtin_pwd(void);

/*** unset.c ***/
int							builtin_unset(int ac, char *av[], t_env **env);

/*** utils.c ***/
int							validate_var_name(const char *name);
t_env						*new_env_with_value(char *key, char *value);

/*** EXECUTION ***/
/*** execution.c ***/
void						execute_cmd(t_shell *mini);

/*** exec_external.c ***/
int							execute_external_cmd(t_cmd *cmd, t_shell *mini);

/*** exec_single.c ***/
int							execute_single_cmd(t_cmd *cmd, t_shell *mini);

/*** exec_multiple.c ***/
int							execute_multiple_cmds(t_shell *mini);

/*** find_executable.c ***/
char						*find_executable(char *cmd, t_env *env_dup);

/*** exec_utils.c ***/
char						**env_list_to_array(t_env *env_dup);
int							*save_std_fds(void);
void						restore_std_fds(int *saved_fds);

/*** builtins_exec.c ***/
int							execute_builtin(t_cmd *cmd, t_shell *mini);
int							is_builtin(const char *cmd,
								t_builtin_cmd *builtin_cmds);
t_builtin_cmd				*init_builtin_cmds(void);

/*** heredoc.c ***/
int							handle_heredoc(char *delimiter);
int							set_heredoc(t_cmd *cmds);

/*** heredoc_utils.c ***/
int							open_heredoc_for_reading(char *tmp_file);
void						process_heredoc_input(int fd, char *tmp_file,
								char *delimiter);

/*** pipes.c ***/
int							create_pipes(t_cmd *cmds);
void						close_all_pipes(t_cmd *cmds);
void						close_unused_pipes(t_cmd *cmds, t_cmd *current);
void						close_cmd_output_pipe(t_cmd *cmd);

/*** redir.c ***/
int							help_setup_redirections(t_cmd *cmds);
int							set_redir(t_cmd *cmds);

/*** redir_utils.c ***/
int							input_redir(char *filename);
int							output_redir(char *filename);
int							append_redir(char *filename);

/*** FAKE GLOBAL ***/
/*** fake_global.c ***/
int							*get_exit_status(void);

/*** MAIN ***/
/*** minishell.c ***/
void						init(t_shell *mini);
int							shell_loop(t_shell *mini);

#endif