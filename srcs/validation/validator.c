/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:22:52 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/23 15:11:20 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	start_check(char *input, int i)
{
	if (input[i] == '|' && input[i + 1] == '|')
		return (print_msg(1, "syntax error - token `||'", 258));
	if (input[i] == '|')
		return (print_msg(1, "syntax error - token `|'", 258));
	if (input[i] == ';' && input[i + 1] == ';')
		return (print_msg(1, "syntax error - token `;;'", 258));
	if (input[i] == ';')
		return (print_msg(1, "syntax error - token `;'", 258));
	return (0);
}

int	finish_check(char *input, int *i)
{
	*i = skip_space_tab(input, *i);
	if (input[*i] == '\0')
		return (print_msg(1, \
						"syntax error -token `newline'", 258));
	if (input[*i] == '|')
		return (print_msg(1, "syntax error - token `|'", 258));
	if (input[*i] == '>')
		return (print_msg(1, "syntax error - token `>'", 258));
	if (input[*i] == '<')
		return (print_msg(1, "syntax error - token `<'", 258));
	if (input[*i] == ';')
		return (print_msg(1, "syntax error - token `;'", 258));
	return (0);
}
int	count_pipe_delim(char *input, int i)
{
	i = skip_space_tab(input, i);
	if (input[i] == '|')
	{
		if (input[i + 1] == '|')
			return (print_msg(1, "syntax error token `||'", 258));
		return (print_msg(1, "syntax error token `|'", 258));
	}
	if (input[i] == ';')
	{
		if (input[i + 1] == ';' || input[i - 1] == ';')
			return (print_msg(1, "syntax error token `;;'", 258));
		return (print_msg(1, "syntax error token `;'", 258));
	}
	return (0);
}
int	count_quote(char *input, int *i, char quote)
{
	while (input[++(*i)])
	{
		if (input[*i] == quote)
			return (0);
	}
	return (print_msg(1, "syntax error with unclosed quotes", 258));
}
int	validator(char *input)
{
	int	i;

	if (!input)
		return (1);
	i = skip_space_tab(input, 0);
	if (input[i] == '|' || input[i] == ';')
		return (start_check(input, i));
	while (input[i])
	{
		if ((input[i] == '|' || input[i] == ';') && \
				count_pipe_delim(input, i + 1))
			return (1);
		if (input[i] == '\'' && count_quote(input, &i, input[i]))
			return (1);
		if (input[i] == '\"' && count_quote(input, &i, input[i]))
			return (1);
		if ((input[i] == '<' || input[i] == '>') && \
				redir_counting(input, &i, input[i]))
			return (1);
		i++;
	}
	return (0);
}