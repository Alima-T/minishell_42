/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:39:49 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/20 12:19:16 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
1. new_arg: Creates a new argument node, duplicates the argument string, and
initializes the node.
2. append_arg: Adds a new node to the end of the linked list of argument nodes.
3. del_first_node: Deletes the first node in the list and frees its memory.
4. del_one_arg: Deletes a specific node and frees its memory.
5. arglst_destroy: Deletes all nodes in the list, freeing all allocated memory.
This code is part of a linked list implementation for managing command-line
arguments in a shell-like environment.
1. new_arg: Создает новый узел аргумента, дублирует строку аргумента и
инициализирует узел.
2. append_arg: Добавляет новый узел в конец связанного списка узлов аргументов.
3. del_first_node: Удаляет первый узел в списке и освобождает его память.
4. del_one_arg: Удаляет конкретный узел и освобождает его память.
5. arglst_destroy: Удаляет все узлы в списке, освобождая всю выделенную память.
Этот код является частью реализации связанного списка для управления аргументами
командной строки в окружении, похожем на shell.
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
	next = (*args)->next;
	free((*args)->arg_val);
	(*args)->arg_val = NULL;
	free((*args));
	*args = next;
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
	free(lst->arg_val);
	lst->arg_val = NULL;
	free(lst);
	lst = NULL;
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
	t_arg	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		del_one_arg(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

/*
 * Создает новый узел аргумента с заданной строкой аргумента.
 * Выделяет память для нового узла и дублирует строку аргумента.
 * @param arg_str Строка аргумента, которая будет сохранена в новом узле.
 * @param mini Указатель на структуру shell (не используется в этой функции).
 * @return Указатель на созданный узел аргумента или NULL,
	если выделение памяти не удалось.
 */
t_arg	*new_arg(char *arg_str, t_shell *mini)
{
	t_arg	*node;

	(void)mini;
	node = (t_arg *)malloc(sizeof(t_arg));
	if (!node)
		return (NULL);
	node->arg_val = ft_strdup(arg_str);
	node->redir_flag = 0;
	node->space_flag_arg = false;
	node->next = NULL;
	free(arg_str);
	return (node);
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
	t_arg	*last;

	if (!lst || !new)
		exit(EXIT_FAILURE);
	if (*lst)
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	else
		*lst = new;
}
