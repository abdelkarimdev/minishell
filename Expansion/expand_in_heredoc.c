/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_in_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 20:59:37 by aazounda          #+#    #+#             */
/*   Updated: 2025/08/13 10:56:27 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	get_expand_len_here(char *content)
{
	char	*var_name;
	size_t	size;
	size_t	sub_size;
	size_t	i;

	if (content == NULL)
		return (0);
	i = 0;
	sub_size = 0;
	size = 0;
	while (content[i])
	{
		if (content[i] == '$')
		{
			var_name = get_var_name(&content[i]);
			size = size + ft_strlen(get_var_value(var_name));
			sub_size = sub_size + (1 + ft_strlen(var_name));
		}
		i++;
	}
	size = (i - sub_size) + size;
	return (size);
}

char	*expand_in_heredoc(char *str)
{
	size_t	i;
	size_t	pos;
	char	*buffer;
	char	*var_name;

	i = 0;
	pos = 0;
	buffer = ft_malloc((get_expand_len_here(str) + 1) * sizeof(char));
	while (str[i])
	{
		if (str[i] == '$')
		{
			var_name = get_var_name(&str[i]);
			set_to_buffer(buffer, &pos, get_var_value(var_name));
			i = i + 1 + ft_strlen(var_name);
		}
		else
			buffer[pos++] = str[i++];
	}
	buffer[pos] = '\0';
	return (ft_strdup(buffer));
}
