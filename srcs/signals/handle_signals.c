/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:27:26 by tbolsako          #+#    #+#             */
/*   Updated: 2025/01/06 17:26:39 by aokhapki         ###   ########.fr       */
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

void	sig_interact_ctrl_c(int signal)
{
	(void) signal;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	*get_exit_status() = 1;
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
	struct sigaction	sa_int;
	struct termios		new_termios;

	sa_int.sa_handler = sig_interact_ctrl_c;
	sigemptyset(&sa_int.sa_mask);
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, &sig_interact_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	tcgetattr(STDIN_FILENO, &new_termios);
	new_termios.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

/*handles the SIGQUIT signal by printing the signal number with a "Quit: " prefix to the error stream, 
frees the mem allocated, sets the exit status to 131 (stand exit code for SIGQUIT), 
обрабатывает сигнал SIGQUIT: выводит сообщение "Quit:" и номер сигнала в поток ошибок, 
освобождает память и устанавливает статус выхода в 131.
*/
void	sig_non_interact_quit(int signal)
{
	char	*nb;
	/* for CTR + \   */
	if (signal == SIGQUIT)
	{
		nb = ft_itoa(signal);
		ft_putstr_fd("ˆ\\Quit: ", STDERR_FILENO);
		ft_putendl_fd(nb, STDERR_FILENO);
		free(nb);
		nb = NULL;
		*get_exit_status() = 131;
	}
	// for CTR+C
	if (signal == SIGINT)
		write(1, "^C\n", 3);
}

/* handles the SIGINT signal, Output a newline character to the error stream.
ft_putstr_fd("\n", STDERR_FILENO); выводит новую строку в поток ошибок для форматирования вывода в терминале.
*exit_status() = 130; устан-т статус выхода в 130 (означает, что процесс был прерван сигналом SIGINT)
*/
void	sig_non_interact_ctrl_c(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDERR_FILENO);
	*get_exit_status() = 130;
}

/* This function sets up signal handlers for the non-interactive shell.
signal(SIGTERM, SIG_DFL); // - Для сигнала SIGTERM уст-ся станд. действие SIG_DFL (завершение процесса)
*/

void	sigs_non_interact_shell(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = sig_non_interact_quit;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	signal(SIGQUIT, sig_non_interact_quit);
}
