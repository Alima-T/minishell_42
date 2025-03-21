/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:15:14 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/21 17:02:20 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h" 

int	count_pipe_delim(char *input, int i)
{
	i = skip_space_tab(input, i);
	if (input[i] == '|')
	{
		if (input[i + 1] == '|')
			return (print_msg(1, "syntax error near unexpected token `||'", \
				258));
		return (print_msg(1, "syntax error near unexpected token `|'", 258));
	}
	if (input[i] == ';')
	{
		if (input[i + 1] == ';' || input[i - 1] == ';')
			return (print_msg(1, "syntax error near unexpected token `;;'", \
				258));
		return (print_msg(1, "syntax error near unexpected token `;'", 258));
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
	return (print_msg(1, "syntax error - unclosed quotes", 258));
}
