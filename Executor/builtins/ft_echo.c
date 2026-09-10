/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-el- <aben-el-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 09:20:43 by aben-el-          #+#    #+#             */
/*   Updated: 2025/08/14 08:53:12 by aben-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_option(char *option)
{
	int	i;

	i = 1;
	while (option[i])
	{
		if (option[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_list *cmd)
{
	int	flag;

	flag = 0;
	while (cmd && ft_strncmp(cmd->content, "-n", 2) == 0)
	{
		if (check_option(cmd->content))
			flag = 1;
		else
			break ;
		cmd = cmd->next;
	}
	while (cmd)
	{
		if (cmd != NULL)
		{
			ft_putstr_fd(cmd->content, STDOUT_FILENO);
			cmd = cmd->next;
		}
		if (cmd)
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (flag == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
