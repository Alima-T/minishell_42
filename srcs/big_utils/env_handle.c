/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:45:29 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/02 15:26:33 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
The env_handle.c file manages environment variables in a shell-like environment. 
It provides functions for searching, deleting, counting, and updating environment variables stored in a linked list.

Function explanations:
find_in_env: searches for a key in the list and returns the val or NULL.
env_del_node: deletes a node, freeing memory for the key, val, and the node itself.
env_destroy: destroys the entire list by removing nodes and setting the list pointer to NULL.
env_dup_size: counts the number of nodes in the list or returns -1 if the list is empty.
update_env: updates the val of an environment variable in the list, creating a new string for the variable.

Файл env_handle.c управляет переменными окружения в оболочке. 
Он предоставляет функции для поиска, удаления, подсчета и обновления переменных в связанном списке.

Объяснение функций:
find_in_env: ищет ключ в списке и возвращает значение или NULL.
env_del_node: удаляет узел, освобождает память для ключа, значения и самого узла.
env_destroy: уничтожает весь список, удаляя узлы и устанавливая указатель на NULL.
env_dup_size: подсчитывает количество узлов в списке или возвращает -1, если список пуст.
update_env: обновляет значение переменной окружения в списке, создав новую строку для переменной.
*/

/**
 * Находит значение для указанного ключа в связанном списке переменных окружения.
 * Проходит по списку, чтобы найти ключ, и возвращает соответствующее значение.
 * @param env_dup Указатель на начало списка переменных окружения.
 * @param key Ключ переменной окружения, которую нужно найти.
 * @return Значение, связанное с ключом, или NULL, если ключ не найден.
 */
char	*find_in_env(t_env *env_dup, char *key)
{
	if (!env_dup || !key)
		return (NULL);
	while (env_dup)
	{
		if (!ft_strcmp(env_dup->key, key))
			return (env_dup->val);// Возврат значения, если ключ совпадает
		env_dup = env_dup->next;
	}
	return (NULL);
}

/**
 * Удаляет отдельный узел переменной окружения из связанного списка.
 * Освобождает память, выделенную для узла и связанных с ним строк.
 * @param list Указатель на узел переменной окружения для удаления.
 * free(list); // Free the node itself
 * list = NULL;// Установка указателя узла в NULL (не влияет на вызывающую функцию)
 */
void	env_del_node(t_env *list)
{
	if (!list)
		return;
	free(list->line);
	list->line = NULL;
	free(list->key);
	list->key = NULL;
	free(list->val);
	list->val = NULL;
	free(list);
	list = NULL;
}

/**
* Counts the number of nodes in the environment variable linked list
* and returns the number of environment variables present. 
* вычисляет количество элементов в связном списке `env_dup` (переменные окружения),
* и возвращает это количество. Если список пустой (NULL), возвращается -1.
* @param env_dup A pointer to the head of the environment variable list.
* @return The count of environment variables, or -1 if the list is NULL.
*/
int	env_dup_size(t_env *env_dup)
{
	int	count;
	
	if (!env_dup)
		return (-1);
	count = 0;
	while (env_dup)
	{
		env_dup = env_dup->next;
		count++;
	}
	return (count);
}

/**
 * Изменяет значение переменной окружения в связанном списке.
 * Обновляет значение, связанное с указанным ключом, и создает новую строку.
 * @param env_dup Указатель на начало списка переменных окружения.
 * @param key Ключ переменной окружения для изменения.
 * @param val Новое значение для переменной окружения.
 */
void	update_env(t_env *env_dup, char *key, char *val)
{
	if (!env_dup || !key || !val)
		return ;
	while (env_dup)
	{
		if (!ft_strcmp(env_dup->key, key))
		{
			if (env_dup->line)
				free(env_dup->line);
			env_dup->line = ft_strjoin_con(key, "=", val);
			if (env_dup->val)
				free(env_dup->val);
			env_dup->val = ft_strdup(val);
			return ;
		}
		env_dup = env_dup->next;
	}
}

/**
 * Destroys the entire environment variable linked list.Уничтожает весь связанный список переменных окружения.
 * It iterates through the list and deletes each node.Проходит по списку и удаляет каждый узел.
 * @param list A double pointer to the head of the environment variable list.
 * 	*list = NULL;	// Set the head of the list to NULL (list is now empty)
 */
void	env_destroy(t_env **list)
{
	t_env	*temp;

	if (!list)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		env_del_node(*list);
		*list = temp;
	}
	*list = NULL;
}
