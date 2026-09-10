/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:35:58 by aazounda          #+#    #+#             */
/*   Updated: 2025/08/16 09:44:35 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_fd_node(t_collect **_head, void *_value)
{
	t_collect	*tmp;
	t_collect	*new_node;

	if (_head == NULL || _value == NULL)
		return ;
	new_node = ft_malloc(sizeof(t_collect));
	new_node->value = _value;
	new_node->next = NULL;
	if (*_head == NULL)
	{
		*_head = new_node;
		return ;
	}
	tmp = *_head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	return ;
}

void	collect_fds(int option, int fd)
{
	static t_collect	*fds;
	int					*new_fd;

	if (option == COLLECT_FD)
	{
		new_fd = ft_malloc(sizeof(int));
		*new_fd = fd;
		add_fd_node(&fds, new_fd);
	}
	else if (option == CLOSE_ALL)
	{
		while (fds)
		{
			if (fds->value)
				close(*(int *)fds->value);
			fds = fds->next;
		}
		fds = NULL;
	}
}
