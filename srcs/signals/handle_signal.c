/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:27:26 by tbolsako          #+#    #+#             */
/*   Updated: 2025/01/06 15:43:36 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
Readline is a library used in Unix-like systems that provides line-editing capabilities for command-line interfaces. 
It allows users to edit the current line of input, navigate through their command history, 
and manage text efficiently with familiar keyboard shortcuts (e.g., arrow keys, Ctrl commands).
Readline — это lib, в Unix-подобных системах, предоставляет возможн. редактирования строк для интерфейсов командной строки. 
Она позволяет пользователям редактировать текущую строку ввода, перемещаться по истории команд и эффективно управлять текстом 
с использованием знакомых сочетаний клавиш (например, стрелок, комбинаций с Ctrl).
*/
/**
 * Handles the Ctrl+C (SIGINT) signal in an interactive shell. 
 * It prevents the program from terminating, 
 * clears the current input line, displays a new prompt, 
 * and updates the global exit status to 1 (error code).
 */
 
void	sig_interact_ctrl_c(int signal)
{
	(void) signal;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	*exit_status() = 1;
}
/*обеспечивает устойчивость и отзывчивость оболочки к сигналам, 
как от пользователя, так и от системы, позволяя выполнять команды 
и прерывать их без неожиданного завершения программы.
SIGTERM Ignored: Prevents the shell from being accidentally terminated 
by external commands or signals, ensuring it remains active until explicitly exited.
SIGINT Custom Handler: Allows the shell to handle interruptions (e.g., Ctrl+C) gracefully. 
Instead of terminating the shell, it can stop the current operation, clear the input, and return to the prompt for further commands.
SIGQUIT Ignored: Prevents the shell from being terminated or creating a core dump 
when the user presses Ctrl+\ (SIGQUIT), maintaining a clean and controlled session.
*/
void	sigs_interact_shell(void)
{
	signal(SIGTERM, SIG_IGN); 
	signal(SIGINT, &sig_interact_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
// This function handles the SIGQUIT signal.
void	sig_non_interact_quit(int signal)
{
	char	*nb;

	nb = ft_itoa(signal); 
	ft_putstr_fd("Quit: ", STDERR_FILENO); // Output the message "Quit: " to the error stream.
	ft_putendl_fd(nb, STDERR_FILENO); // Output the signal number to the error stream with a newline.
	free(nb); 
	nb = NULL; // Set the pointer to the signal number string to NULL.
	*exit_status() = 131; // Set the exit status to 131.
}

// This function handles the SIGINT signal.
void	sig_non_interact_ctrl_c(int signal)
{
	(void)signal; 
	ft_putstr_fd("\n", STDERR_FILENO); // Output a newline character to the error stream.
	*exit_status() = 130; // Set the exit status to 130.
}

// This function sets up signal handlers for the non-interactive shell.
void	sigs_non_interact_shell(void)
{
	signal(SIGTERM, SIG_DFL); // Set the default handler for the SIGTERM signal.
	signal(SIGINT, sig_non_interact_ctrl_c); // Set the handler for the SIGINT signal.
	signal(SIGQUIT, sig_non_interact_quit); // Set the handler for the SIGQUIT signal.
}
