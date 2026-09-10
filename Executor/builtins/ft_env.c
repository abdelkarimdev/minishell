/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 06:23:32 by aben-el-          #+#    #+#             */
/*   Updated: 2025/08/16 11:47:19 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	print_environemnt(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '=') != NULL)
		{
			ft_putstr_fd(env[i], 1);
			write(1, "\n", 1);
		}
		i++;
	}
}

int	ft_env(t_list *cmd)
{
	char	**env;

	env = ft_envp(NULL);
	if (!cmd)
		print_environemnt(env);
	else
	{
		ft_print_error("minishell: too many arguments\n");
		return (1);
	}
	return (0);
}
