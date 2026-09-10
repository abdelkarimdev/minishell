/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 10:57:12 by aben-el-          #+#    #+#             */
/*   Updated: 2025/08/16 13:56:07 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**build_args(t_list *args_lst)
{
	char	**args;
	size_t	len;
	size_t	i;

	len = ft_t_lst_size(args_lst);
	args = ft_malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (args_lst)
	{
		args[i] = args_lst->content;
		args_lst = args_lst->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

static void	execute_child(char *path, char **args)
{
	setup_child_signals(0);
	execve(path, args, ft_envp(NULL));
	perror("execve");
	exit(1);
}

int	execute_external(t_list *cmd)
{
	char	**args;
	int		pid;
	char	*path;
	int		status;

	status = EXIT_SUCCESS;
	path = found_command(cmd->content);
	if (!path)
		return (*ft_exit_code());
	args = build_args(cmd);
	setup_ignore_signals();
	pid = fork();
	if (pid < 0)
		return (setup_signals(0), 1);
	else if (pid == 0)
		execute_child(path, args);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			handle_sigexit_child(WTERMSIG(status));
		setup_signals(0);
	}
	return (ft_exit_status(status));
}

int	execute_external_without_fork(t_list *cmd)
{
	char	**args;
	char	*path;
	int		status;

	path = NULL;
	status = EXIT_SUCCESS;
	path = found_command(cmd->content);
	if (!path)
		return (*ft_exit_code());
	args = build_args(cmd);
	execve(path, args, ft_envp(NULL));
	perror("execve");
	return (1);
}
