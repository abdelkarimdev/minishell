/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:43:45 by aazounda          #+#    #+#             */
/*   Updated: 2025/08/16 11:32:03 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_strcpy(char *result, char const *str1, char const *str2)
{
	int	i;
	int	j;

	i = 0;
	while (str1[i])
	{
		result[i] = str1[i];
		i++;
	}
	j = 0;
	while (str2[j])
	{
		result[i + j] = str2[j];
		j++;
	}
	result[i + j] = '\0';
}

char	*ft_strjoin(char const *str1, char const *str2)
{
	char	*result;
	size_t	size;

	if (str1 == NULL && str2 == NULL)
		return (NULL);
	if (str1 == NULL)
		return (ft_strdup(str2));
	else if (str2 == NULL)
		return (ft_strdup(str1));
	size = ft_strlen(str1) + ft_strlen(str2) + 1;
	result = (char *)malloc(size * sizeof(char));
	collector(0, result);
	ft_strcpy(result, str1, str2);
	return (result);
}
