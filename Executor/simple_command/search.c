/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-el- <aben-el-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:51:22 by aben-el-          #+#    #+#             */
/*   Updated: 2025/08/15 18:28:26 by aben-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_valid_absolute_relative_path(char **cmd_path, char *cmd)
{
	struct stat	st;

	if (ft_strchr(cmd, '/'))
	{
		if (stat(cmd, &st) == -1)
		{
			if (errno == ENOENT)
				return (ft_print_error("minishell: %s: %s\n", cmd,
						strerror(errno)), 127);
			else
				return (ft_print_error("minishell: %s: %s\n", cmd,
						strerror(errno)), 126);
		}
		else if (S_ISDIR(st.st_mode))
			return (ft_print_error("minshell: %s: Is a directory\n", cmd), 126);
		*cmd_path = ft_strdup(cmd);
		if (access(*cmd_path, X_OK) == 0)
			return (0);
		else
			return (ft_print_error("minshell: %s: %s\n", *cmd_path,
					strerror(errno)), 126);
	}
	return (1);
}

static int	is_exist(char *cmd_path, struct stat *st, int *access_flag)
{
	if (stat(cmd_path, st) == 0 && !S_ISDIR(st->st_mode))
	{
		if (access(cmd_path, X_OK) == 0)
			return (0);
		*access_flag = 1;
	}
	return (1);
}

int	check_command_in_path(char **cmd_path, char *path, char *cmd)
{
	char		*tmp;
	struct stat	st;
	char		**dirs;
	int			i;
	int			access_flag;

	access_flag = 0;
	if (path == NULL || (path != NULL && path[0] == '\0'))
		path = ft_strdup("./");
	dirs = ft_split(path, ':');
	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin("/", cmd);
		*cmd_path = ft_strjoin(dirs[i], tmp);
		if (is_exist(*cmd_path, &st, &access_flag) == 0)
			return (0);
		i++;
	}
	if (access_flag == 1)
		return (ft_print_error("minshell: %s: Permission denied\n",
				*cmd_path), 126);
	*ft_exit_code() = 127;
	return (1);
}

char	*found_command(char *cmd)
{
	char	*path;
	char	*cmd_path;
	int		status;

	cmd_path = NULL;
	status = is_valid_absolute_relative_path(&cmd_path, cmd);
	if (status == 1)
	{
		path = ft_getenv("PATH");
		status = check_command_in_path(&cmd_path, path, cmd);
		if ((!path && status == 1) || (path && path[0] == '\0' && status == 1))
		{
			ft_print_error("minshell : %s: No such file or directory\n", cmd);
			return (NULL);
		}
		else if (status == 1)
		{
			ft_print_error("minshell: %s: command not found\n", cmd);
			return (NULL);
		}
	}
	if (status == 0)
		return (cmd_path);
	*ft_exit_code() = status;
	return (NULL);
}
