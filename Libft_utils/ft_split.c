/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:47:27 by aazounda          #+#    #+#             */
/*   Updated: 2025/08/16 13:31:02 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	words_counter(char const *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static size_t	my_strlen(char const *str, char c)
{
	size_t	count;

	count = 0;
	while (*str != c && *str != '\0')
	{
		count++;
		str++;
	}
	return (count);
}

static char	*skip(char const *str, char c)
{
	while (*str)
	{
		if (*str != c)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

char	**ft_split(char const *str, char c)
{
	char	**arr;
	size_t	size;
	size_t	i;

	if (str == NULL)
		return (NULL);
	size = words_counter(str, c) + 1;
	arr = malloc(size * sizeof(char *));
	collector(0, arr);
	i = 0;
	while (i < (size - 1))
	{
		str = skip(str, c);
		arr[i] = ft_substr(str, 0, my_strlen(str, c));
		str = str + ft_strlen(arr[i]) + 1;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
