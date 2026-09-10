/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:56:06 by aazounda          #+#    #+#             */
/*   Updated: 2025/08/16 10:15:58 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *str)
{
	char	*new_location_str;
	size_t	i;

	i = 0;
	new_location_str = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	collector(COLLECT, new_location_str);
	while (str[i])
	{
		new_location_str[i] = str[i];
		i++;
	}
	new_location_str[i] = '\0';
	return (new_location_str);
}
