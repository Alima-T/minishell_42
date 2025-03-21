/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:22:52 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/21 17:44:56 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	start_check(char *input, int i)
{
	if (input[i] == '|' && input[i + 1] == '|')
		return (print_msg(1, "syntax error near unexpected token `||'", 258));
	if (input[i] == '|')
		return (print_msg(1, "syntax error near unexpected token `|'", 258));
	if (input[i] == ';' && input[i + 1] == ';')
		return (print_msg(1, "syntax error near unexpected token `;;'", 258));
	if (input[i] == ';')
		return (print_msg(1, "syntax error near unexpected token `;'", 258));
	return (0);
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
		if ((input[i] == '|' || input[i] == ';') && count_pipe_delim(input, i
				+ 1))
			return (1);
		if (input[i] == '\'' && count_quote(input, &i, input[i]))
			return (1);
		if (input[i] == '\"' && count_quote(input, &i, input[i]))
			return (1);
		if ((input[i] == '<' || input[i] == '>') && redir_counting(input, &i,
				input[i]))
			return (1);
		i++;
	}
	return (0);
}
