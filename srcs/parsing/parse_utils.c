/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:33:17 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/21 17:12:07 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*is_slash(char *input, int *i)
{
	char	*tmp_1;
	char	*tmp_2;

	tmp_1 = ft_substr(input, 0, *i);
	tmp_2 = ft_strdup(input + *i + 1);
	free(input);
	input = NULL;
	input = ft_strjoin(tmp_1, tmp_2);
	free(tmp_1);
	free(tmp_2);
	(*i)++;
	return (input);
}

bool	is_token_separator(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>');
}

int	skip_space_tab(char *inp, int i)
{
	while (inp[i] && (ft_strchr(" ", inp[i]) || ft_strchr("\t", inp[i])))
		i++;
	return (i);
}
