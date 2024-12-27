/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:45:29 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/27 18:02:46 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
Explanation of Functions:
1.find_in_env:
This function searches for a specific key in the linked list of environment variables. If the key is found, it returns the corresponding value; otherwise, it returns NULL.
2. env_lst_del_node:
This function deletes a single node from the environment variable linked list. It frees the memory allocated for the node's line, key, and value strings, and then frees the node itself.
3.env_destroy:
This function destroys the entire linked list of environment variables. It iterates through the list, deleting each node using envl_lstdelone, and finally sets the head of the list to NULL.
4. env_copy_lst_size:
This function counts the number of nodes in the environment variable linked list. It returns the count of environment variables present or -1 if the list is NULL.
5. change_value_in_env_copy:
This function updates the value of an environment variable in the linked list. It searches for the specified key, and if found, it updates the value and constructs a new line representation of the variable.
Summary:
The env_handle.c file is responsible for managing environment variables in a shell-like environment. It provides functions to find, delete, count, and update environment variables stored in a linked list. This functionality is essential for a shell to manage its environment and provide users with the ability to interact with environment variables effectively.

Объяснение функций:
find_in_env: ищет заданный ключ в связанном списке переменных окружения. Если ключ найден, возвращается соответствующее значение, иначе возвращается NULL.
env_lst_del_node: удаляет один узел из связанного списка переменных окружения, освобождает память, выделенную для строки узла, ключа и значения, а затем освобождает сам узел.
env_destroy: уничтожает весь связанный список переменных окружения. Она проходит по списку, удаляя каждый узел с помощью env_lst_del_node, и в конце устанавливает указатель на начало списка в NULL.
env_copy_lst_size: подсчитывает кол-во узлов в связанном списке переменных окружения, возвращает кол-во переменных окружения или -1, если список равен NULL.
change_value_in_env_copy: обновляет значение переменной окружения в связанном списке, ищет указанный ключ, и если находит его, обновляет значение и создает новую строку, представляющую переменную.

Файл env_handle.c отвечает за управление переменными окружения в среде, подобной оболочке. Он предоставляет функции для поиска, удаления, подсчета и обновления переменных окружения, хранящихся в связанном списке. Эта функциональность важна для работы оболочки, чтобы она могла эффективно управлять окружением и предоставлять пользователям возможность взаимодействовать с переменными окружения.
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
	if (!env_dup || !key) // Проверка, если список или ключ равны NULL
		return (NULL); // Возврат NULL, если один из них равен NULL
	while (env_dup) // Проход по связанному списку
	{
		if (!ft_strcmp(env_dup->key, key)) // Сравнение текущего ключа с искомым ключом
			return (env_dup->value); // Возврат значения, если ключ совпадает
		env_dup = env_dup->next; // Переход к следующему узлу
	}
	return (NULL); // Возврат NULL, если ключ не найден
}

/**
 * Удаляет отдельный узел переменной окружения из связанного списка.
 * Освобождает память, выделенную для узла и связанных с ним строк.
 *
 * @param lst Указатель на узел переменной окружения для удаления.
 */
void	env_lst_del_node(t_env *lst) // del_env_node
{
	if (!lst)
		return; // Exit if the node is NULL
	free(lst->line); // Free the line string
	lst->line = NULL; // Set the line pointer to NULL
	free(lst->key); // Free the key string
	lst->key = NULL; // Set the key pointer to NULL
	free(lst->value); // Free the value string
	lst->value = NULL; // Set the value pointer to NULL
	free(lst); // Free the node itself
	lst = NULL; // Set the node pointer to NULL // Установка указателя узла в NULL (не влияет на вызывающую функцию)
}

/**
 * Destroys the entire environment variable linked list.Уничтожает весь связанный список переменных окружения.
 * It iterates through the list and deletes each node.Проходит по списку и удаляет каждый узел.
 * @param lst A double pointer to the head of the environment variable list.
 */
void	env_lst_destroy(t_env **lst)
{
	t_env	*tmp; // Temporary pointer to hold the next node

	if (!lst)
		return;
	while (*lst) // While there are nodes in the list
	{
		tmp = (*lst)->next; // Store the next node
		env_lst_del_node(*lst); // Delete the current node
		*lst = tmp; // Move to the next node
	}
	*lst = NULL; // Set the head of the list to NULL (list is now empty)
}

/**
* Counts the number of nodes in the environment variable linked list.  Счет кол-ва узлов в связанном списке переменных окружения.
* It returns the number of environment variables present.
* @param env_dup A pointer to the head of the environment variable list.
* @return The count of environment variables, or -1 if the list is NULL.
*/
int	env_lst_copy_size(t_env *env_dup) 
{
	int		count; // Counter for the number of nodes

	if (!env_dup) // Check if the list is NULL
		return (-1); // Return -1 if the list is NULL
	count = 0; // Initialize the count
	while (env_dup) // Traverse the linked list Проход по связанному списку
	{
		env_dup = env_dup->next; // Move to the next node
		count++; // Increment the count
	}
	return (count); // Return the total count of nodes
}

/**
 * Изменяет значение переменной окружения в связанном списке.
 * Обновляет значение, связанное с указанным ключом, и создает новую строку.
 *
 * @param env_dup Указатель на начало списка переменных окружения.
 * @param key Ключ переменной окружения для изменения.
 * @param val Новое значение для переменной окружения.
 */
void	change_value_in_env_copy(t_env *env_dup, char *key, char *val)
{
	if (!env_dup || !key || !val) // Check for NULL
		return; 
	while (env_dup) // Traverse the linked list
	{
		if (!ft_strcmp(env_dup->key, key)) // Compare the current key with the target key Сравнение текущего ключа с искомым ключом
		{
			if (env_dup->line) // If the line exists, free it
				free(env_dup->line);
			env_dup->line = ft_strjoin_con(key, "=", val); // Create the new line
			if (env_dup->value) // If the value exists, free it
				free(env_dup->value);
			env_dup->value = ft_strdup(val); // Duplicate the new value
			return; // Exit after updating
		}
		env_dup = env_dup->next; // Move to the next node
	}
}
