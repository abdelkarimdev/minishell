/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-el- <aben-el-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:11:24 by aazounda          #+#    #+#             */
/*   Updated: 2025/08/15 18:03:31 by aben-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*save_s;

	save_s = (unsigned char *)s;
	while (n)
	{
		*save_s = 0;
		save_s++;
		n--;
	}
}
