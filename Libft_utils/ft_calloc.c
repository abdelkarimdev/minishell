/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:11:16 by aazounda          #+#    #+#             */
/*   Updated: 2025/08/16 10:15:38 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;

	result = malloc(nmemb * size);
	collector(0, result);
	ft_bzero(result, nmemb * size);
	return (result);
}
