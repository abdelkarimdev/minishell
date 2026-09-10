/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-el- <aben-el-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 10:43:40 by aben-el-          #+#    #+#             */
/*   Updated: 2025/08/14 09:10:04 by aben-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**ft_sort_env(char **_envp)
{
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	len = 0;
	while (_envp[i + 1])
	{
		j = i + 1;
		while (_envp[j])
		{
			len = get_len(_envp[i], _envp[j]);
			if (ft_strncmp(_envp[i], _envp[j], len) > 0)
				ft_swap(&_envp[i], &_envp[j]);
			j++;
		}
		i++;
	}
	return (_envp);
}

void	print_str_with_quotes(char *str)
{
	size_t	i;
	size_t	len;
	int		flag;

	len = ft_strlen(str);
	i = 0;
	flag = 0;
	while (i < len)
	{
		write(1, &str[i], 1);
		if (!flag && str[i] == '=')
		{
			write(1, "\"", 1);
			flag = 1;
		}
		i++;
	}
	if (flag)
		write(1, "\"", 1);
	write(1, "\n", 1);
}

void	print_env(char **envp)
{
	int		i;

	i = 0;
	envp = ft_sort_env(envp);
	while (envp[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		print_str_with_quotes(envp[i]);
		i++;
	}
}
