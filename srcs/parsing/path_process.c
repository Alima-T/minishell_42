

#include "../../minishell.h"

// Fetches the directories listed in the PATH environment variable and splits them into an array.
// Извлекает каталоги, перечисленные в PATH переменной среды, и разбивает их на массив.
char **get_paths(t_shell *mini)
{
	char **paths;
	char *path;
	
	path = find_in_env(mini->env_dup, "PATH");
	if (!path)
		return (NULL);
		paths = ft_split(path, ':');
		return (paths);
}

//Checks if the input contains an executable path by looking for the '/' character.
int is_path(char *str)
{
	int i;

	i = 0;
	while((str[i]) && (!ft_isalnum (str[i])))
	{
		if(str[i] == '/')
			return (1);
		i++;
	}
	return (0);	
}

/*
Resolves the full executable path for a given command by:
Returning the command directly if it already includes an executable path.
Searching for the command in the directories listed in the PATH environment variable.
If a match is found (exists and is executable), it returns the full path; otherwise, it returns NULL.
Определяет полный путь к исполняемому файлу для заданной команды с помощью:
Возврат команды напрямую, если она уже содержит путь к исполняемому файлу.
Поиск команды в каталогах, указанных в PATHпеременной среды.
Если совпадение найдено (существует и является исполняемым), возвращается полный путь; в противном случае возвращается NULL.
*/

char *path_process(t_shell *mini, char *cmd)
{
	char *path;
	char **paths;
	int	i;
	
	i = 0;
	if (is_path(cmd))
		return (cmd);
	paths = get_paths(mini);
	if(!paths)
		return (NULL);
	while(paths[i])
	{
		path = ft_strjoin_con(paths[i], "/", cmd);
		if(!access(path, F_OK | X_OK))
		{
			free_array(paths);
			return(path);
		}
		free(path);
		i++;
	}
	free_array(paths);
	return(NULL);
}
