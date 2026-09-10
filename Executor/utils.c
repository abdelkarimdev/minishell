/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-el- <aben-el-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 04:41:00 by aazounda          #+#    #+#             */
/*   Updated: 2025/08/15 20:07:50 by aben-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lst_size(t_command *cmd)
{
	t_command	*head;
	int			size;

	head = cmd;
	size = 0;
	while (head)
	{
		size++;
		head = head->next;
	}
	return (size);
}

int	ft_t_lst_size(t_list *cmd)
{
	int	size;

	size = 0;
	while (cmd)
	{
		size++;
		cmd = cmd->next;
	}
	return (size);
}

int	check_arg(char *s)
{
	int	i;

	i = 0;
	if (!s[i])
		return (0);
	while (s[i] == ' ')
		i++;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	while (s[i] == ' ')
		i++;
	if (s[i] != '\0')
		return (0);
	return (1);
}

int	ft_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (*ft_exit_code());
}

int	check_is_builtin(t_list *cmd)
{
	if (ft_strcmp("echo", cmd->content) == 0)
		return (1);
	else if (ft_strcmp("cd", cmd->content) == 0)
		return (1);
	else if (ft_strcmp("pwd", cmd->content) == 0)
		return (1);
	else if (ft_strcmp("export", cmd->content) == 0)
		return (1);
	else if (ft_strcmp("env", cmd->content) == 0)
		return (1);
	else if (ft_strcmp("unset", cmd->content) == 0)
		return (1);
	else if (ft_strcmp("unset", cmd->content) == 0)
		return (1);
	else if (ft_strcmp("exit", cmd->content) == 0)
		return (1);
	return (0);
}
