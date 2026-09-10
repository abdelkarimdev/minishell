/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 10:38:44 by aazounda          #+#    #+#             */
/*   Updated: 2025/08/14 10:39:22 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_whitespace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char	**copy_envp(char **envp, int flag)
{
	char	**_envp;
	int		i;
	int		size;

	size = 0;
	i = 0;
	while (envp[size])
		size++;
	if (flag == ADD)
		size++;
	_envp = ft_malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (envp[i])
	{
		_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	_envp[i] = NULL;
	_envp[size] = NULL;
	return (_envp);
}

void	tmpfiles_collector(int option, char *new_file)
{
	static t_list	*files;

	if (new_file != NULL && option == COLLECT_TMPFILE)
		add_node(&files, ft_strdup(new_file), 0);
	else if (option == UNLINK_ALL)
	{
		while (files)
		{
			unlink(files->content);
			files = files->next;
		}
	}
}
