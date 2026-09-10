/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-el- <aben-el-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:23:57 by aben-el-          #+#    #+#             */
/*   Updated: 2025/08/14 09:16:02 by aben-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	execute_builtin(t_list *args)
{
	if (args && ft_strcmp(args->content, "echo") == 0)
		return (ft_echo(args->next));
	else if (args && ft_strcmp(args->content, "cd") == 0)
		return (ft_cd(args->next));
	else if (args && ft_strcmp(args->content, "pwd") == 0)
		return (ft_pwd(args));
	else if (args && ft_strcmp(args->content, "export") == 0)
		return (ft_export(args->next));
	else if (args && ft_strcmp(args->content, "env") == 0)
		return (ft_env(args->next));
	else if (args && ft_strcmp(args->content, "unset") == 0)
		return (ft_unset(args->next));
	else if (args && ft_strcmp(args->content, "exit") == 0)
		return (ft_exit(args->next));
	return (0);
}
