/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 10:20:39 by aazounda          #+#    #+#             */
/*   Updated: 2025/08/16 13:29:08 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	add_collect(t_collect **_head, void *_value)
{
	t_collect	*tmp;
	t_collect	*new_node;

	if (_head == NULL || _value == NULL)
		return (-1);
	new_node = (t_collect *)malloc(sizeof(t_collect));
	if (!new_node)
		return (-1);
	new_node->value = _value;
	new_node->next = NULL;
	if (*_head == NULL)
	{
		*_head = new_node;
		return (0);
	}
	tmp = *_head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	return (0);
}

static void	clear_collects(t_collect *head)
{
	if (head == NULL)
		return ;
	clear_collects(head->next);
	free(head->value);
	free(head);
}

void	collector(int option, void *new)
{
	static t_collect	*head;

	if (option == COLLECT)
	{
		if (new == NULL)
		{
			clear_collects(head);
			exit(EXIT_FAILURE);
		}
		else if (add_collect(&head, new) == -1)
		{
			clear_collects(head);
			exit(EXIT_FAILURE);
		}
	}
	else if (option == CLEAR)
	{
		clear_collects(head);
		head = NULL;
	}
}

void	*ft_malloc(size_t size)
{
	void	*new;

	new = malloc(size);
	collector(COLLECT, new);
	return (new);
}

void	ft_exit_clean(int exit_code)
{
	collect_fds(CLOSE_ALL, -1);
	collector(CLEAR, NULL);
	environment_copy(FREE, NULL);
	exit(exit_code);
}
