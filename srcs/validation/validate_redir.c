/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:36:13 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/23 15:06:19 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	redir_reading(char *input, int *i)
{
	(*i)++;
	if (input[*i] == '\0' || input[*i] == '>')
		return (print_msg(1, "syntax error - token `newline'", 258));
	if (input[*i] == '|')
		return (print_msg(1, "syntax error - token `|'", 258));
	if (input[*i] == '<')
	{
		(*i)++;
		return (finish_check(input, i));
	}
	else
		return (finish_check(input, i));
}

int	redir_writing(char *input, int *i)
{
	(*i)++;
	if (input[*i] == '\0' || input[*i] == '|')
		return (print_msg(1, "syntax error - token `newline'", 258));
	if (input[*i] == '<')
		return (print_msg(1, "syntax error - token `<'", 258));
	if (input[*i] == '>')
	{
		(*i)++;
		return (finish_check(input, i));
	}
	else
		return (finish_check(input, i));
}

int	redir_counting(char *input, int *i, char redir)
{
	if (redir == '>' && redir_writing(input, i))
		return (1);
	if (redir == '<' && redir_reading(input, i))
		return (1);
	(*i)--;			//добавлено на случай ls >'1'
	return (0);
}