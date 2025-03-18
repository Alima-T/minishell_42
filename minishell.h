/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:01:06 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/18 18:15:22 by aokhapki         ###   ########.fr       */
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
	char					*val;
	struct s_env			*next;
}							t_env;

typedef struct s_arg
{
	char					*arg_val;
	int						redir_flag;
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
	struct s_redir			*redir;
	struct s_cmd			*next;
}							t_cmd;

/*** BIG_UTILS  ***/
/*** args_handle.c ***/
void						del_first_node(t_arg **args);
void						del_one_arg(t_arg *lst);
void						arglst_destroy(t_arg **lst);
void						append_arg(t_arg **lst, t_arg *new);
t_arg						*new_arg(char *arg_str, t_shell *mini);

/*** cmds_handle.c ***/
void						redir_del_node(t_redir *redir_node);
void						redir_destroy(t_redir **redir_list);
void						cmd_del_node(t_cmd *cmd_node);
void						cmdlst_destroy(t_cmd **list);

/*** fd_and_heredoc_handle.c ***/
int							open_helper(char *path, char flag);
char						*generate_heredoc_filename(void);

/*** env_handle.c ***/
void						env_destroy(t_env **list);
void						update_env(t_env *env_dup, char *key, char *val);
char						*find_in_env(t_env *env_dup, char *key);
int							count_env_vars(t_env *env_dup);

/*** level_change.c ***/
void						shell_level_down(t_shell *mini);
void						shell_level_up(t_shell *mini);

/*** mem_mngt.c ***/
void						cleanup_cmd(t_cmd *cmd);
void						cleanup_heredoc_files(void);

/*** mem_utils.c ***/
void						*mem_allocator(size_t size);
void						free_array(char **array);
void						free_builtin_cmds(t_builtin_cmd *builtin_cmds);
void						free_shell_mem_enhanced(t_shell *mini);

/*** PARSING ***/
/*** args_process.c ***/
int							find_boundary(char *input, int pos, int *flag);
int							is_redir(char *arg);
void						set_redirect(t_arg *args);
void						lex_input(char *input, t_arg **args, t_shell *mini);
t_arg						*args_process(t_shell *mini);

/*** cmds_create ***/
int							find_cmd(t_arg *args);
char						**turn_cmd_to_array(t_arg *args, int lists_count);
void						append_cmd(t_cmd **list, t_cmd *new);
t_cmd						*create_cmds_lst(t_arg *args);

/*** cmds_process.c ***/
void						process_cmds_and_redirs(t_shell *mini);
char						*is_slash(char *input, int *i);
char						*parse_special_chars(char *input, t_env *env_dup);
t_cmd						*cmds_process(t_shell *mini);

/*** dollar_process.c ***/
char						*replace_env(char *input, int start, int end,
								t_env *env_dup);
char						*find_in_env(t_env *env_dup, char *key);
char						*question_handle(char *input, int begin, int *i);
char						*is_dollar(char *input, int *i, t_env *env_dup);
char						is_valid_char(char c);

/*** envp_process.c ***/
char						*copy_value(char *env_part);
char						*copy_key(char *env_part);
void						append_env(t_env **list, t_env *new);
t_env						*new_env(char *env_str);
t_env						*copy_envp(char **envp);

/*** parse_utils.c ***/
int							skip_space_tab(char *inp, int i);

/*** parser.c ***/
int							parser(t_shell *mini, t_env *env_dup);
int							valid_helper(t_shell *mini);

/*** path_process.c ***/
char						**get_paths(t_shell *mini);
char						*path_process(t_shell *mini, char *cmd_name);
int							is_path(char *str);

/*** quotes_process.c ***/
char						*combine_subs(char *input, int start, int end);
char						*is_quote(char *input, int *i);
char						*is_db_quote(char *input, int *i, t_env *env_dup);

/*** redirect_process.c ***/
int							redir_first(t_arg **args, t_redir **rdr);
void						redir_add_end(t_redir **list, t_redir *new);
t_redir						*redirect_process(t_arg **args);
t_redir						*redir_new(char *type, char *name);

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

/*** PRINTING  ***/
/*** print_msgs.c ***/
int							print_msg(int return_val, char *msg, int exit_stat);
void						print_cmds(t_cmd *cmds);
void						print_args(t_arg *args);
void						print_env_copy(t_env *env_dup);
void						print_redir(t_cmd *cmds);

/*** print_errmsg.c ***/
void						cmd_not_found_msg(char *message);
void						errmsg(char *message);

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
int							builtin_echo(char **args);

/*** env.c ***/
int							builtin_env(t_env *env_dup);

/*** exit.c ***/
int							builtin_exit(int ac, char *av[], t_shell *mini);
void						exit_with_error(t_shell *mini, char *arg, char *msg,
								int status);

/*** exit_helper.c ***/
int							is_numeric_str(char *str);
void						handle_non_digit(t_shell *mini, char *str);

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

/*** exec_helper.c ***/
char						**env_list_to_array(t_env *env_dup);
char						*find_executable(char *cmd, t_env *env_dup);

/*** builtins_exec.c ***/
int							execute_builtin(t_cmd *cmd, t_shell *mini);
int							is_builtin(const char *cmd,
								t_builtin_cmd *builtin_cmds);
t_builtin_cmd				*init_builtin_cmds(void);

/*** heredoc_redir.c ***/
int							setup_redirections(t_cmd *cmds);
int							set_redir(t_cmd *cmds);
int							handle_heredoc(char *delimiter);
int							set_heredoc(t_cmd *cmds);

/*** pipes.c ***/
int							create_pipes(t_cmd *cmds);
void						close_all_pipes(t_cmd *cmds);

/*** expansion.c ***/
char						*expand_env_vars(char *str, t_env *env_dup);
char						*get_env_var_value(t_env *env_dup,
								const char *name);

/*** FAKE GLOBAL ***/
/*** fake_global.c ***/
int							*get_exit_status(void);

/*** MAIN ***/
/*** minishell.c ***/
void						init(t_shell *mini);
int							shell_loop(t_shell *mini);


#endif