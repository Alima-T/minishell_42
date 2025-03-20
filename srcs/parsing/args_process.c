/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:32:40 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/20 23:07:26 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
// void	lex_input(char *input, t_arg **args, t_shell *mini)
// {
// 	int		i;
// 	int		start;
// 	int		end;
// 	int		fl;
// 	char	*tmp;
// 	int		i_old;
// 	bool	has_space;
// 	t_arg	*new_node;

// 	i = 0;
// 	fl = 0;
// 	while (input[i] != '\0')
// 	{
// 		i_old = i;
// 		i = skip_space_tab(input, i);
// 		// if (i_old != i)
// 		has_space = false;
// 		// else
// 		// 	has_space = true;
// 		start = i;
// 		if (input[i] == '\0')
// 			return ;
// 		end = find_boundary(input, i, &fl);
// 		if (!input[end] || input[end] == ' ' || input[end] == '\t')
// 			has_space = true;
// 		i = end;
// 		if (fl != 0)
// 		{
// 			tmp = ft_substr(input, start, end - start);
// 			if (ft_strcmp(tmp, "\0"))
// 			{
// 				new_node = new_arg(tmp, mini);
// 				new_node->space_flag_arg = has_space;
// 				append_arg(args, new_node);
// 			}
// 			else
// 				free(tmp);
// 			new_node = new_arg(ft_substr(input, end, fl), mini);
// 			new_node->space_flag_arg = false;
// 			append_arg(args, new_node);
// 			i += fl;
// 			fl = 0;
// 		}
// 		else
// 		{
// 			new_node = new_arg(ft_substr(input, start, end - start), mini);
// 			new_node->space_flag_arg = has_space;
// 			append_arg(args, new_node);
// 		}
// 	}
// }
static void	sngl_cmd(t_shell *mini, t_arg **args)
{
	char	*tmp;
	t_arg	*new_node;

	tmp = ft_substr(mini->input, mini->nums.start, mini->nums.end
			- mini->nums.start);
	if (ft_strcmp(tmp, "\0"))
	{
		new_node = new_arg(tmp, mini);
		new_node->space_flag_arg = mini->nums.has_space;
		append_arg(args, new_node);
	}
	else
		free(tmp);
	new_node = new_arg(ft_substr(mini->input, mini->nums.end, mini->nums.fl),
			mini);
	new_node->space_flag_arg = false;
	append_arg(args, new_node);
	mini->nums.i += mini->nums.fl;
	mini->nums.fl = 0;
}

static void	multi_cmd(t_shell *mini, t_arg **args)
{
	t_arg	*new_node;

	new_node = new_arg(ft_substr(mini->input, mini->nums.start, \
		mini->nums.end - mini->nums.start), mini);
	new_node->space_flag_arg = mini->nums.has_space;
	append_arg(args, new_node);
}

void	lex_input(t_arg **args, t_shell *mini)
{
	mini->nums.i = 0;
	mini->nums.fl = 0;
	mini->nums.i_old = 0;
	while (mini->input[mini->nums.i] != '\0')
	{
		mini->nums.i_old = mini->nums.i;
		mini->nums.i = skip_space_tab(mini->input, mini->nums.i);
		mini->nums.has_space = false;
		mini->nums.start = mini->nums.i;
		if (mini->input[mini->nums.i] == '\0')
			return ;
		mini->nums.end = find_boundary(mini->input, mini->nums.i,
				&mini->nums.fl);
		if (!mini->input[mini->nums.end] || mini->input[mini->nums.end] == ' '
			|| mini->input[mini->nums.end] == '\t')
			mini->nums.has_space = true;
		mini->nums.i = mini->nums.end;
		if (mini->nums.fl != 0)
			sngl_cmd(mini, args);
		else
			multi_cmd(mini, args);
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
	lex_input(&(mini->args), mini);
	set_redirect(mini->args);
	return (mini->args);
}
