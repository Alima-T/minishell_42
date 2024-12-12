/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:33:17 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/12 19:26:21 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

// Function to skip over spaces and tabs in an input string
// Returns the index after all consecutive spaces/tabs
int	skip_space_tab(char *inp, int i)
{
	while (inp[i] && (ft_strchr(" ", inp[i]) || ft_strchr("\t", inp[i])))
		i++;
	return (i);
}
/* IOA - Input(read from a file)/Output (write to a file)/Append (append data to a file)
Purpose: Opens a file with specific permissions based on the flag
Parameters:
  - path: file path to open
  - flag: 'I' for input (read), 'O' for output (write), 'A' for append
Returns: file descriptor or exits on error
Note: Sets global error status (g_ext_stats) on failure
O_CREAT: Same as above; it creates the file if it doesn’t exist.
O_WRONLY: Again, the file is opened for write-only access.
O_TRUNC: If the file already exists, this flag ensures that the file's contents are truncated to zero length. 
In other words, it will delete the existing content of the file and start fresh, which is useful if you want to overwrite the file's content.
O_APPEND: This flag makes sure that any data written to the file is appended to the end of the file rather than overwriting it. 
If the file already exists, the new data will be added after the existing content.

0644: These are the permissions for the newly created file if it doesn't exist. The permissions are set in octal format:
Octal (0): Indicates the number is in octal.
Owner (6): Read and write permissions (rw-).
Group (4): Read-only permissions (r--).
Others (4): Read-only permissions (r--)

O_CREAT: Создает файл, если он не существует.
O_WRONLY: Открывает файл только для записи.
O_TRUNC: Усекает (очищает) файл, если он существует.
O_APPEND: Добавляет к файлу (сохраняет существующее содержимое)
0644: Устанавливает права доступа к файлу (чтение/запись для владельца, только чтение для остальных).
*/

int	open_fd(char *path, char flag)
{
	int	fd = -1;

	// Open file based on the flag
	if (flag == 'I') // Read-only mode
		fd = open(path, O_RDONLY);
	else if (flag == 'O') // Write-only, truncate
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (flag == 'A') // Write-only, append
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)// Handle errors during file opening
	{
		print_msg(1, strerror(errno), 1);  // Print the error message
		g_ext_stats = 1;                    // Set global error status
		exit(g_ext_stats);                  // Exit the program
	}
	return (fd); // Return the valid file descriptor
}
// Function: handle_redirections
// Purpose: Handles redirections in the given command and opens appropriate file descriptors
// Parameters:
//   - cmds: command structure containing redirection information
// Note: Supports three types of redirections:
//   - "<"  : Input redirection
//   - ">"  : Output redirection (overwrite)
//   - ">>" : Output redirection (append)
void	set_redirection(t_cmdl *cmds)
{
	t_redir	*tmp;
	int		it;

	if (cmds == NULL)
		return ;
	it = 0;
	tmp = (t_redir *) cmds->redir;
	while (tmp)
	{
		if (ft_strcmp("<", tmp->type) == 0)
			cmds->in = open_fd(tmp->name, 'I');
		if (ft_strcmp(">", tmp->type) == 0)
			cmds->out = open_fd(tmp->name, 'O');
		if (ft_strcmp(">>", tmp->type) == 0)
			cmds->out = open_fd(tmp->name, 'A');
		tmp = tmp->next;
		it++;
	}
}


int print_msg(int return_val, char *message, int ext_stat)
{
	// Print a formatted prefix "[minishell ]$ " to stderr
	// BEGIN(49, 32) and CLOSE could be macros that add color or special formatting.
	// 49: Default background color (terminal's default background).
	// 32: Green text color (foreground).
	// 9: Red background.
	// 15: White text.
	ft_putstr_fd(BEGIN(9, 15)"[minishell ]$ "CLOSE, STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);	
	// Set the global variable g_ext_stats to the value of ext_stat
	// This is typically used to track the exit status of commands or errors.
	g_ext_stats = ext_stat;	
	// Return the value of ret_val
	// This value is typically used to signal success or failure to the caller.
	return (return_val);
}