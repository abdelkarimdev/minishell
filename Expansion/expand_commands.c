/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 09:18:31 by aazounda          #+#    #+#             */
/*   Updated: 2025/08/14 10:31:26 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	set_tokens(t_list *node, t_list *new_list)
{
	t_list	*tmp;

	if (!new_list || !node)
		return ;
	tmp = node->next;
	node->content = new_list->content;
	node->type = new_list->type;
	node->next = new_list->next;
	while (node->next)
	{
		node = node->next;
	}
	node->next = tmp;
}

static int	expand_args(t_list **args)
{
	t_list	*new_list;

	if (args == NULL || *args == NULL)
		return (1);
	expand_args(&(*args)->next);
	new_list = expand_word((*args)->content, 1);
	if (new_list)
		set_tokens(*args, new_list);
	else
		(*args) = (*args)->next;
	return (1);
}

int	expand_cmds(t_command *cmds)
{
	t_command	*current;

	if (cmds == NULL)
		return (-1);
	current = cmds;
	while (current)
	{
		expand_args(&current->args);
		current = current->next;
	}
	return (0);
}
