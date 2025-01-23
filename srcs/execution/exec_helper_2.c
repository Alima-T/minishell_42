/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:09:43 by tbolsako          #+#    #+#             */
/*   Updated: 2025/01/23 20:51:31 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Expands environment variables.
 * @param str
 * @return
 */
char	*expand_env_vars(char *str)
{
	char	*result;
	char	*var;
	char	*value;
	char	*temp;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			if (str[i] == '?')
			{
				value = ft_itoa(*get_exit_status());
				temp = ft_strjoin(result, value);
				free(result);
				result = temp;
				free(value);
				i++;
			}
			else
			{
				var = ft_strdup("");
				while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				{
					temp = ft_strjoin_char(var, str[i]);
					free(var);
					var = temp;
					i++;
				}
				value = getenv(var);
				free(var);
				if (value)
				{
					temp = ft_strjoin(result, value);
					free(result);
					result = temp;
				}
			}
		}
		else
		{
			temp = ft_strjoin_char(result, str[i]);
			free(result);
			result = temp;
			i++;
		}
	}
	return (result);
}

/**
 * IOA
 *	- Input(read from a file)/Output (write to a file)/
 *    Append (append data to a file)
 * Purpose: Opens a file with specific permissions based on the flag
 * Parameters:
 *  - path: file path to open
 *  - flag: 'I' for input (read), 'O' for output (write), 'A' for append
 * Returns: file descriptor or exits on error
 * Note: Sets global error status (g_ext_stats) on failure
 * O_CREAT: Same as above; it creates the file if it doesn’t exist.
 * O_WRONLY: Again, the file is opened for write-only access.
 * O_TRUNC: If the file already exists, this flag ensures that the file's
 * 			contents are truncated to zero length.
 * In other words, it will delete the existing content of the file and start
 * fresh, which is useful if you want to overwrite the file's content.
 * O_APPEND: This flag makes sure that any data written to the file is appended
 * 			to the end of the file rather than overwriting it.
 * If the file already exists, the new data will be added after the existing
 * content.
 *
 * 0644: These are the permissions for the newly created file if it doesn't
 * exist. The permissions are set in octal format:
 * Octal (0): Indicates the number is in octal.
 * Owner (6): Read and write permissions (rw-).
 * Group (4): Read-only permissions (r--).
 * Others (4): Read-only permissions (r--)
 *
 * O_CREAT: Создает файл, если он не существует.
 * O_WRONLY: Открывает файл только для записи.
 * O_TRUNC: Усекает (очищает) файл, если он существует.
 * O_APPEND: Добавляет к файлу (сохраняет существующее содержимое)
 * 0644: Устанавливает права доступа к файлу (чтение/запись для владельца,
 * только чтение для остальных).
 * if (fd == -1)// Handle errors during file opening
 * @param path File path to open.
 * @param flag 'I' for input (read), 'O' for output (write), 'A' for append.
 * @return File descriptor or exits on error.
 */
int	open_fd(char *path, char flag)
{
	int	fd;

	fd = -1;
	// Open file based on the flag
	// Read-only mode
	if (flag == 'I')
		fd = open(path, O_RDONLY);
	else if (flag == 'O')
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (flag == 'A')
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		print_msg(1, strerror(errno), 1);
		*get_exit_status() = 1;
		exit(*get_exit_status());
	}
	// Return the valid file descriptor
	return (fd);
}

/**
 * Handles redirs in the given command and opens appropriate file descriptors.
 *
 * Note: Supports three types of redirs:
 * - "<"  : Input redir
 * - ">"  : Output redir (overwrite)
 * - ">>" : Output redir (append)
 * @param cmds Command structure containing redir information.
 */
void	set_redir(t_cmd *cmds)
{
	t_redir	*tmp;
	int		fd;

	if (cmds == NULL)
		return ;
	tmp = (t_redir *)cmds->redir;
	while (tmp)
	{
		if (ft_strcmp(tmp->type, "<") == 0)
			fd = open_fd(tmp->name, 'I');
		if (ft_strcmp(tmp->type, ">") == 0)
			fd = open_fd(tmp->name, 'O');
		if (ft_strcmp(tmp->type, ">>") == 0)
			fd = open_fd(tmp->name, 'A');
		else
		{
			tmp = tmp->next;
			continue ;
		}
		if (fd == -1)
		{
			perror("open_fd");
			exit(EXIT_FAILURE);
		}
		if (ft_strcmp(tmp->type, ">") == 0 || ft_strcmp(tmp->type, ">>") == 0)
			dup2(fd, STDOUT_FILENO);
		else if (ft_strcmp(tmp->type, "<") == 0)
			dup2(fd, STDOUT_FILENO);
		close(fd);
		tmp = tmp->next;
	}
}
