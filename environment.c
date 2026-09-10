/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:49:25 by aazounda          #+#    #+#             */
/*   Updated: 2025/08/14 11:09:09 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_normal_strdup(const char *str)
{
	char	*new_location_str;
	size_t	i;

	i = 0;
	new_location_str = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!new_location_str)
		return (NULL);
	while (str[i])
	{
		new_location_str[i] = str[i];
		i++;
	}
	new_location_str[i] = '\0';
	return (new_location_str);
}

static void	free_all(char **arr, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**copy_arr(char **envp)
{
	char	**copy;
	size_t	i;
	size_t	size;

	size = 0;
	i = 0;
	while (envp[size])
		size++;
	copy = malloc(sizeof(char *) * (size + 1));
	if (!copy)
		ft_exit_clean(2);
	i = 0;
	while (i < size)
	{
		copy[i] = ft_normal_strdup(envp[i]);
		if (!copy[i])
		{
			free_all(copy, i);
			ft_exit_clean(2);
		}
		i++;
	}
	copy[size] = NULL;
	return (copy);
}

void	free_arr(char **arr)
{
	size_t	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**environment_copy(int option, char **envp)
{
	static char	**env_copy;
	char		**save;

	if (envp && option == 0)
	{
		save = env_copy;
		env_copy = copy_arr(envp);
		free_arr(save);
	}
	else if (option == 1)
		free_arr(env_copy);
	else if (option == 2)
		return (env_copy);
	return (NULL);
}
