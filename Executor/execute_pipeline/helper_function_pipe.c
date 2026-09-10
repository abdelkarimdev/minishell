/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 02:57:28 by aben-el-          #+#    #+#             */
/*   Updated: 2025/08/14 08:39:29 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_fds(int **fds, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		i++;
	}
}
