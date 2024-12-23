/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:34:37 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/23 15:17:02 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int main() {
//     // Create a linked list of command arguments
//     t_arg *args = create_arg_node("arg1");
//     args->next = create_arg_node("arg2");
//     args->next->next = create_arg_node("arg3");

//     // Count the number of arguments in the linked list
//     int lists_count = find_cmd(args);

//     // Convert the linked list to an array
//     char **args_array = turn_cmd_to_array(args, lists_count);
//     if (!args_array) {
//         fprintf(stderr, "Failed to convert arguments to array\n");
//         free_arg_list(args); // Clean up the linked list
//         return (1); // Exit with an error code
//     }

//     // Print the resulting array
//     for (int i = 0; i < lists_count; i++) {
//         printf("args_array[%d]: %s\n", i, args_array[i]);
//         free(args_array[i]); // Free each duplicated string
//     }
//     free(args_array); // Free the array itself

//     // Free the linked list
//     free_arg_list(args);

//     return (0); // Successful execution
// }

/**
 * Frees all allocated resources in the shell structure and exits the program.
 *
 * @param mini A pointer to the shell structure.
 * @param exit_status The exit status code to return.
 */
void	free_exit(t_shell *mini, int exit_status)
{
	// Free the argument list
	if (mini->args)
	{
		list_destroy(&mini->args);
			// Assuming list_destroy frees the argument list
	}
	// Free the input string if it was allocated
	if (mini->input)
	{
		free(mini->input);
		mini->input = NULL;
	}
	// Free any other resources in the shell structure
	// For example, if you have an environment copy, free it here
	if (mini->env_copy)
	{
		// Assuming env_copy is a linked list or an array of strings
		// Free each environment variable if necessary
		// Example: free_env_list(mini->env_copy);
	}
	// Exit the program with the specified exit status
	exit(exit_status);
}

void	execute_cmnd(t_shell *mini)
{
	char *args[3]; // array to hold cmnd and arg (echo + arg)
	// check if the cmnd is echo
	if (ft_strncmp(mini->args->arg_val, "echo", 4) == 0)
	{
		args[0] = mini->args->arg_val; // 1st arg is the cmnd
		// check if there is a next arg
		if (mini->args->next != NULL)
			args[1] = mini->args->next->arg_val; // 2nd arg (if exists)
		else
			args[1] = NULL; // no 2nd arg
		args[2] = NULL;     // Null-terminate the arg list
		// execute the echo cmnd
		builtin_echo(args);
	}
	else
		printf("Command not recognized.\n");
}

int	main(int ac, char *av[])
{
	t_shell mini; // shell structure to hold input and args
	mini.env_copy = NULL; // init env copy
	mini.args = NULL;     // init args
	// ignore unused params
	(void)av;
	(void)ac;
	// main loop for the shell
	while (1)
	{
		// read input from the user
		parser(&mini, mini.env_copy); // read input and process it

// короче, ниже закоменченный код (1) если ты его используешь программа на echo hello
// работает, затем выводит ошибку reading output и потом полность выходит из минишелла
// (2) если не используешь, программа делает операцию echo hello дважды, НО полностью
// не выходит из минишелла и можно там работать дальше

		// if (!mini.input)
		// {
		// 	perror("Error reading input");
		// 	break ;
		// }
		// process the input into args
		// mini.args = process_args(&mini);
		if (mini.args)
			execute_cmnd(&mini);
		free(mini.input);  // free the input line after processing
		mini.input = NULL; // reset input for the next iteration
	}
	// cleanup and exit
	free_exit(&mini, *exit_status()); // free resources and exit
	return (0);
}
