/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:06:32 by aazounda          #+#    #+#             */
/*   Updated: 2025/08/16 10:16:10 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char			*result;
	unsigned int	i;

	if (str == NULL)
		return (NULL);
	if (start >= ft_strlen(str))
		return ((char *)ft_calloc(1, sizeof(char)));
	if (len > ft_strlen(str + start))
		len = ft_strlen(str + start);
	result = (char *)malloc(len * sizeof(char) + 1);
	collector(0, result);
	i = 0;
	while (str[start + i] && len)
	{
		result[i] = str[start + i];
		i++;
		len--;
	}
	result[i] = '\0';
	return (result);
}
