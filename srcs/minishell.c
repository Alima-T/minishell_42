/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:34:37 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/19 15:35:32 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main() {
    // Create a linked list of command arguments
    t_arg *args = create_arg_node("arg1");
    args->next = create_arg_node("arg2");
    args->next->next = create_arg_node("arg3");

    // Count the number of arguments in the linked list
    int lists_count = find_cmd(args);

    // Convert the linked list to an array
    char **args_array = turn_cmd_to_array(args, lists_count);
    if (!args_array) {
        fprintf(stderr, "Failed to convert arguments to array\n");
        free_arg_list(args); // Clean up the linked list
        return 1; // Exit with an error code
    }

    // Print the resulting array
    for (int i = 0; i < lists_count; i++) {
        printf("args_array[%d]: %s\n", i, args_array[i]);
        free(args_array[i]); // Free each duplicated string
    }
    free(args_array); // Free the array itself

    // Free the linked list
    free_arg_list(args);

    return 0; // Successful execution
}