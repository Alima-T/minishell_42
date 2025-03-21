/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:36:13 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/21 17:44:31 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	finish_check(char *input, int *i)
{
	*i = skip_space_tab(input, *i);
	if (input[*i] == '\0')
		return (print_msg(1, "syntax error near unexpected token `newline'", \
			258));
	if (input[*i] == '|')
		return (print_msg(1, "syntax error near unexpected token `|'", 258));
	if (input[*i] == '>')
		return (print_msg(1, "syntax error near unexpected token `>'", 258));
	if (input[*i] == '<')
		return (print_msg(1, "syntax error near unexpected token `<'", 258));
	if (input[*i] == ';')
		return (print_msg(1, "syntax error near unexpected token `;'", 258));
	return (0);
}

static int	redir_writing(char *input, int *i)
{
	(*i)++;
	if (input[*i] == '\0' || input[*i] == '|')
		return (print_msg(1, "syntax error near unexpected token `newline'", \
			258));
	if (input[*i] == '<')
		return (print_msg(1, "syntax error near unexpected token `<'", 258));
	if (input[*i] == '>')
	{
		(*i)++;
		return (finish_check(input, i));
	}
	else
		return (finish_check(input, i));
}

static int	redir_reading(char *input, int *i)
{
	(*i)++;
	if (input[*i] == '\0' || input[*i] == '>')
		return (print_msg(1, "syntax error near unexpected token `newline'", \
			258));
	if (input[*i] == '|')
		return (print_msg(1, "syntax error near unexpected token `|'", 258));
	if (input[*i] == '<')
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
	(*i)--;
	return (0);
}
