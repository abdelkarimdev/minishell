/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-el- <aben-el-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 09:26:58 by aben-el-          #+#    #+#             */
/*   Updated: 2025/08/14 09:10:25 by aben-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_remove_var(char **envp, char	*var)
{
	int	j;
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
		{
			j = i;
			while (envp[j + 1])
			{
				envp[j] = envp[j + 1];
				j++;
			}
			envp[j] = NULL;
			break ;
		}
		i++;
	}
}

int	ft_unset(t_list *cmd)
{
	char	**envp;

	envp = ft_envp(NULL);
	while (cmd)
	{
		ft_remove_var(envp, cmd->content);
		cmd = cmd->next;
	}
	ft_envp(envp);
	return (0);
}
