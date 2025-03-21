/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:28:37 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/21 17:49:47 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	print_msg(int ret_val, char *message, int ext_stat)
{
	ft_putstr_fd(BEGIN"minishell: "CLOSE, STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	*get_exit_status() = ext_stat;
	return (ret_val);
}
