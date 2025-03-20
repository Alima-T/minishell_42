/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:32:40 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/20 12:44:42 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Checks if the given argument is a redirection operator.
 * @param arg The argument string to check.
 * @return 1 if the argument is a redirection operator, 0 otherwise.
 */
int	is_redir(char *arg)
{
	if ((ft_strcmp(arg, ">") == 0)
		|| (ft_strcmp(arg, ">>") == 0)
		|| (ft_strcmp(arg, "<") == 0)
		|| (ft_strcmp(arg, "<<") == 0))
		return (1);
	return (0);
}

/**
 * Marks redirection flags in the argument list.
 * Sets the redir_flag for redirection operators and their following arguments.
 * @param args A pointer to the list of arguments.
 */
void	set_redirect(t_arg *args)
{
	while (args)
	{
		if (is_redir(args->arg_val) == 1)
		{
			args->redir_flag = 1;
			args->next->redir_flag = 2;
			args = args->next->next;
		}
		else if (args)
			args = args->next;
	}
}

/*
int *fl:
Указатель на целое число, которое будет обновлено для указания условий анализа:
0: По умолчанию, никаких особых условий не обнаружено.
1: Одно перенаправление ( <, |, >).
2: Двойное перенаправление (например, <<или >>).
*/
int	find_boundary(char *input, int pos, int *fl)
{
	char	quote;

	while (input[pos])
	{
		if (input[pos] == '\'' || input[pos] == '\"')
		{
			quote = input[pos];
			pos++;
			while (input[pos] && input[pos] != quote)
				pos++;
			pos++;
			return (pos);
		}
		if (ft_strchr(" \t<|>", input[pos]))
		{
			if (ft_strchr("<|>", input[pos]))
				*fl = 1;
			if (ft_strchr("<>", input[pos]) && ft_strchr("<>", input[pos + 1]))
				*fl = 2;
			return (pos);
		}
		pos++;
	}
	return (pos);
}

/**
 * Splits the input string into arguments and handles special operators.
 * @param input The input string to be split.
 * @param args A double pointer to the list of arguments.
 * int	fl; - special handling for operators or redirs
 * @param mini A pointer to the shell structure.
 */
void	lex_input(char *input, t_arg **args, t_shell *mini)
{
	int		i;
	int		start;
	int		end;
	int		fl;
	char	*tmp;
	int		i_old;
	bool	has_space;
	t_arg	*new_node;

	i = 0;
	fl = 0;
	while (input[i] != '\0')
	{
		i_old = i;
		i = skip_space_tab(input, i);
		if (i_old != i)
			has_space = true;
		else
			has_space = false;
		start = i;
		if (input[i] == '\0')
			return ;
		end = find_boundary(input, i, &fl);
		i = end;
		if (fl != 0)
		{
			tmp = ft_substr(input, start, end - start);
			if (ft_strcmp(tmp, "\0"))
			{
				new_node = new_arg(tmp, mini);
				new_node->space_flag_arg = has_space;
				append_arg(args, new_node);
			}
			else
				free(tmp);
			new_node = new_arg(ft_substr(input, end, fl), mini);
			new_node->space_flag_arg = false;
			append_arg(args, new_node);
			i += fl;
			fl = 0;
		}
		else
		{
			new_node = new_arg(ft_substr(input, start, end - start), mini);
			new_node->space_flag_arg = has_space;
			append_arg(args, new_node);
		}
	}
}

/**
 * Processes the arguments from the shell structure.
 * Splits the input string into arguments and marks redirection flags.
 * @param mini A pointer to the shell structure containing input and arguments.
 * @return A pointer to the list of processed arguments.
 */
t_arg	*args_process(t_shell *mini)
{
	lex_input(mini->input, &(mini->args), mini);
	set_redirect(mini->args);
	return (mini->args);
}
