/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:39:49 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/02 17:37:05 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
1. new_arg: Creates a new argument node, duplicates the argument string, and initializes the node.
2. append_arg: Adds a new node to the end of the linked list of argument nodes.
3. del_first_node: Deletes the first node in the list and frees its memory.
4. del_one_arg: Deletes a specific node and frees its memory.
5. arglst_destroy: Deletes all nodes in the list, freeing all allocated memory.
This code is part of a linked list implementation for managing command-line arguments in a shell-like environment.

1. new_arg: Создает новый узел аргумента, дублирует строку аргумента и инициализирует узел.
2. append_arg: Добавляет новый узел в конец связанного списка узлов аргументов.
3. del_first_node: Удаляет первый узел в списке и освобождает его память.
4. del_one_arg: Удаляет конкретный узел и освобождает его память.
5. arglst_destroy: Удаляет все узлы в списке, освобождая всю выделенную память.
Этот код является частью реализации связанного списка для управления аргументами командной строки в окружении, похожем на shell.
*/
/**
 * Удаляет первый узел в списке аргументов.
 * Освобождает память, выделенную для строки аргумента и самого узла.
 * Deletes the first node in the argument list.
 * Frees the memory allocated for the argument string and the node itself.
 * @param args A double pointer to the head of the argument list.
 */
void	del_first_node(t_arg **args)
{
	t_arg	*next;

	if (!args || !(*args))
		return ;
	next = (*args)->next;	// Store the next node
	free((*args)->arg_val);	// Free the arg string of the first node
	(*args)->arg_val = NULL;	// Set the arg string ptr to NULL 
	free((*args));	// Free the first node
	*args = next;	// Update the head to the next node
}

/**
 * Deletes a specific argument node and frees its memory.
 * Удаляет конкретный узел аргумента и освобождает его память.
 * @param lst A pointer to the argument node to be deleted.
 */
void	del_one_arg(t_arg *lst)
{
	if (!lst)
		return ;
	free(lst->arg_val);	// Free arg string
	lst->arg_val = NULL;	// Set arg string ptr to NULL
	free(lst);	// Free node itself 
	lst = NULL;	// Set node ptr to NULL (note: this does not affect the caller)
}


/**
 * Destroys the entire argument list by deleting each node.
 * Frees all allocated memory for the argument strings and nodes.
 * Уничтожает весь список аргументов, удаляя каждый узел.
 * Освобождает всю выделенную память для строк аргументов и узлов.
 * @param lst A double ptr to the head of the argument list.
 */
void	arglst_destroy(t_arg **lst)
{
	t_arg	*tmp;	// Temporary pointer to hold the next node

	if (!lst)	// Check for NULL
		return ;
	while (*lst)	// While there are nodes in the list
	{
		tmp = (*lst)->next;	// Store the next node
		del_one_arg(*lst);	// Delete the current node
		*lst = tmp;	// Move to the next node
	}
	*lst = NULL;	// Set the head of the list to NULL (list is now empty)
}

/*
 * Создает новый узел аргумента с заданной строкой аргумента.
 * Выделяет память для нового узла и дублирует строку аргумента.
 * @param arg_str Строка аргумента, которая будет сохранена в новом узле.
 * @param mini Указатель на структуру shell (не используется в этой функции).
 * @return Указатель на созданный узел аргумента или NULL, если выделение памяти не удалось.
 */

t_arg	*new_arg(char *arg_str, t_shell *mini)
{
	t_arg	*el;	// Pointer to the new argument node

	(void)mini;	// Ignore the mini parameter as it's not used
	el = (t_arg *)malloc(sizeof(t_arg));	// Allocate memory for the new node
	if (!el)	// Check if memory allocation failed
		return (NULL);	// Return NULL if allocation fails
	el->arg_val = ft_strdup(arg_str);	// Duplicate the argument string
	el->redir_flag = 0;	// Initialize the redirection flag to 0
	el->next = NULL;	// Set the next pointer to NULL (end of the list)
	free(arg_str);	// Free the original argument string
	return (el);	// Return the newly created node
}

/**
 * Добавляет новый узел аргумента в конец связанного списка.
 * Если список пуст, новый узел становится головой списка.
 * Adds a new argument node to the end of the linked list.
 * If the list is empty, the new node becomes the head of the list.
 * @param lst A double pointer to the head of the list.
 * @param new A pointer to the new argument node, which must to be added.
 */
void	append_arg(t_arg **lst, t_arg *new)
{
	t_arg	*last;	// Pointer to traverse the list
	printf("the arg is: %s\n", new->arg_val); //TO DO delete, added foe debagging
	if (!lst || !new)	// Check for NULL
		exit(EXIT_FAILURE);	// Exit if either is NULL
	if (*lst)	// If the list is not empty
	{
		last = *lst; // Start from the head of the list
		while (last->next) // Traverse to the end of the list
			last = last->next; // Move to the next node
		last->next = new; // Link the new node at the end
	}
	else
		*lst = new; // If the list is empty, set the new node as the head
}
