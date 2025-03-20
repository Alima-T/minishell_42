/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_and_heredoc_handle.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:25:23 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/20 14:27:13 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief IOA - Input(read from a file)/Output (write to a file)/
 * Append (append data to a file)
 *
 * Purpose: Opens a file with specific permissions based on the flag
 *
 * - O_CREAT: Same as above; it creates the file if it doesn’t exist.
 *
 * - O_WRONLY: Again, the file is opened for write-only access.
 *
 * - O_TRUNC: If the file already exists, this flag ensures that the file's
 * contents are truncated to zero length. In other words, it will delete the
 * existing content of the file and start fresh, which is useful if you want
 * to overwrite the file's content.
 *
 * - O_APPEND: This flag makes sure that any data written to the file is
 * appended to the end of the file rather than overwriting it. If the file
 * already exists, the new data will be added after the existing content.
 *
 * 0644: These are the permissions for the newly created file if it doesn't
 * exist.
 *
 * The permissions are set in octal format:
 *
 * - Octal (0): Indicates the number is in octal.
 *
 * - Owner (6): Read and write permissions (rw-).
 *
 * - Group (4): Read-only permissions (r--).
 *
 * - Others (4): Read-only permissions (r--)
 *
 * O_CREAT: Создает файл, если он не существует.
 *
 * O_WRONLY: Открывает файл только для записи.
 *
 * O_TRUNC: Усекает (очищает) файл, если он существует.
 *
 * O_APPEND: Добавляет к файлу (сохраняет существующее содержимое)
 *
 * 0644: Устанавливает права доступа к файлу (чтение/запись для владельца,
 * только чтение для остальных).
 *
 * if (fd == -1)// Handle errors during file opening
 * @param path File path to open.
 * @param flag 'I' for input (read), 'O' for output (write), 'A' for append.
 * @return File descriptor or exits on error.
 *
 * @note Sets global error status (g_ext_stats) on failure.
 */
int	open_helper(char *path, char flag)
{
	int	fd;

	fd = -1;
	if (flag == 'I')
		fd = open(path, O_RDONLY);
	else if (flag == 'O')
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (flag == 'A')
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd(BEGIN "minishell: " CLOSE, STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		*get_exit_status() = 1;
	}
	return (fd);
}

static char	*join_filename_parts(char *pid_str, char *counter_str)
{
	char	*temp_path;
	char	*tmp1;
	char	*result;

	temp_path = ft_strjoin("/tmp/.heredoc_", pid_str);
	if (!temp_path)
		return (NULL);
	tmp1 = ft_strjoin(temp_path, "_");
	free(temp_path);
	if (!tmp1)
		return (NULL);
	result = ft_strjoin(tmp1, counter_str);
	free(tmp1);
	return (result);
}

/**
 * @brief Generates a unique temporary file name for heredoc
 *
 * Creates a unique filename in /tmp based on process ID and a counter
 *
 * @return char* Allocated string with file path or NULL on error
 */
char	*generate_heredoc_filename(void)
{
	static int	counter;
	char		*pid_str;
	char		*counter_str;
	char		*result;
	pid_t		pid;

	counter = 0;
	pid = getpid();
	counter++;
	pid_str = ft_itoa(pid);
	if (!pid_str)
		return (NULL);
	counter_str = ft_itoa(counter);
	if (!counter_str)
	{
		free(pid_str);
		return (NULL);
	}
	result = join_filename_parts(pid_str, counter_str);
	free(pid_str);
	free(counter_str);
	return (result);
}
