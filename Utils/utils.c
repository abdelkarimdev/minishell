/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:47:49 by aazounda          #+#    #+#             */
/*   Updated: 2025/08/16 13:31:12 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char *key)
{
	char	**envp;
	size_t	i;
	size_t	len;

	envp = ft_envp(NULL);
	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strlen_key(envp[i]) > ft_strlen_key(key))
			len = ft_strlen_key(envp[i]);
		else
			len = ft_strlen_key(key);
		if (ft_strncmp(envp[i], key, len) == 0)
			return (&envp[i][ft_strlen_key(key) + 1]);
		i++;
	}
	return (NULL);
}

char	**ft_envp(char **new_env)
{
	static char	**envp;

	if (new_env)
		envp = new_env;
	return (envp);
}

int	*ft_exit_code(void)
{
	static int	status;

	return (&status);
}

int	add_node(t_list **head, char *_content, int _type)
{
	t_list	*new_token;
	t_list	*tmp;

	if (head == NULL)
		return (0);
	if (_content == NULL)
		return (-1);
	new_token = (t_list *)ft_malloc(sizeof(t_list));
	new_token->content = _content;
	new_token->type = _type;
	new_token->next = NULL;
	if (*head == NULL)
	{
		*head = new_token;
		return (1);
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
	return (1);
}

int	add_command(t_command **commands, t_list *_args, t_list *_redirects)
{
	t_command	*tmp;
	t_command	*new_node;

	new_node = ft_malloc(sizeof(t_command));
	new_node->args = _args;
	new_node->redirects = _redirects;
	new_node->next = NULL;
	if (*commands == NULL)
	{
		*commands = new_node;
		return (1);
	}
	tmp = *commands;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	return (1);
}
