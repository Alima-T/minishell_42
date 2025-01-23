/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:33:17 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/23 20:37:53 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Function to skip over spaces and tabs in an input string
// Returns the index after all consecutive spaces/tabs
int	skip_space_tab(char *inp, int i)
{
	while (inp[i] && (ft_strchr(" ", inp[i]) || ft_strchr("\t", inp[i])))
		i++;
	return (i);
}
