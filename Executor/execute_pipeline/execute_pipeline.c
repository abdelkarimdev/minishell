/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-el- <aben-el-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 02:36:28 by aben-el-          #+#    #+#             */
/*   Updated: 2025/08/14 09:12:08 by aben-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	setup_pipes(int **fds, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		fds[i] = ft_malloc(sizeof(int) * 2);
		if (pipe(fds[i]) == -1)
		{
			close_fds(fds, i);
			return (perror("pipe"), -1);
		}
		i++;
	}
	return (0);
}

static int	dup_std_in_out(int i, int size, int **fds)
{
	if (i == 0)
	{
		if (dup2(fds[i][1], STDOUT_FILENO) == -1)
			return (close_fds(fds, i), perror("dup2"), -1);
		close(fds[i][0]);
	}
	else if (i > 0 && i < size - 1)
	{
		if (dup2(fds[i - 1][0], STDIN_FILENO) == -1)
			return (close_fds(fds, i), perror("dup2"), -1);
		if (dup2(fds[i][1], STDOUT_FILENO) == -1)
			return (close_fds(fds, i), perror("dup2"), -1);
	}
	else
	{
		if (dup2(fds[i - 1][0], STDIN_FILENO) == -1)
			return (close_fds(fds, i), perror("dup2"), -1);
		close(fds[i - 1][1]);
	}
	return (0);
}

static void	execute_child_process(t_command *cmd, int **fds, int i, int size)
{
	char	**env;

	setup_child_signals(0);
	env = ft_envp(NULL);
	if (dup_std_in_out(i, size, fds) == -1)
	{
		close_fds(fds, i);
		exit(EXIT_FAILURE);
	}
	close_fds(fds, (size - 1));
	if (cmd->redirects && handel_redirections(cmd) == -1)
	{
		*ft_exit_code() = 1;
		ft_exit_clean(EXIT_FAILURE);
	}
	if (cmd->args && check_is_builtin(cmd->args))
		ft_exit_clean(execute_builtin(cmd->args));
	else if (cmd->args)
		ft_exit_clean(execute_external_without_fork(cmd->args));
	ft_exit_clean(EXIT_SUCCESS);
}

static int	wait_all_pids(pid_t *pids, size_t size)
{
	size_t	i;
	int		status;
	int		sig_num;

	i = 0;
	sig_num = 0;
	while (i < size)
	{
		waitpid(pids[i], &status, 0);
		if (WIFSIGNALED(status))
			sig_num = WTERMSIG(status);
		i++;
	}
	if (sig_num)
		handle_sigexit_child(sig_num);
	setup_signals(0);
	return (status);
}

int	execute_pipeline(t_command *cmds)
{
	pid_t		*pids;
	int			**fds;
	size_t		size;
	size_t		i;

	size = ft_lst_size(cmds);
	pids = ft_malloc(size * sizeof(pid_t));
	fds = ft_malloc((size - 1) * sizeof(int *));
	if (setup_pipes(fds, (size - 1)) == -1)
		return (EXIT_FAILURE);
	i = 0;
	while (cmds && i < size)
	{
		setup_ignore_signals();
		pids[i] = fork();
		if (pids[i] < 0)
			return (setup_signals(0), close_fds(fds, (size - 1)), EXIT_FAILURE);
		else if (pids[i] == 0)
			execute_child_process(cmds, fds, i, size);
		cmds = cmds->next;
		i++;
	}
	close_fds(fds, (size - 1));
	return (ft_exit_status(wait_all_pids(pids, size)));
}
