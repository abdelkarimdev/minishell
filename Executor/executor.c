/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:35:28 by aben-el-          #+#    #+#             */
/*   Updated: 2025/08/16 14:23:28 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_restore(int saved_stdin, int saved_stdout)
{
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (-1);
	}
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
	{
		close(saved_stdin);
		perror("dup2");
		return (-1);
	}
	close(saved_stdin);
	close(saved_stdout);
	return (0);
}

static int	execute_simple_command(t_command *cmd)
{
	int	saved_stdin;
	int	saved_stdout;
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (cmd->redirects)
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
		if (handel_redirections(cmd) == -1)
			return (ft_restore(saved_stdin, saved_stdout), EXIT_FAILURE);
	}
	if (cmd->args && check_is_builtin(cmd->args))
		exit_code = execute_builtin(cmd->args);
	else if (cmd->args)
		exit_code = execute_external(cmd->args);
	if (cmd->redirects)
	{
		if (ft_restore(saved_stdin, saved_stdout) == -1)
			return (1);
	}
	return (exit_code);
}

int	executor(t_command *cmd)
{
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (ft_lst_size(cmd) == 1)
		exit_code = execute_simple_command(cmd);
	else
		exit_code = execute_pipeline(cmd);
	return (exit_code);
}
