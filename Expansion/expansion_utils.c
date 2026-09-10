/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:53:47 by aazounda          #+#    #+#             */
/*   Updated: 2025/08/16 13:28:21 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_var_name(char *content)
{
	char	*var_name;
	size_t	len;
	size_t	i;

	content = content + 1;
	if (content == NULL)
		return (NULL);
	len = 0;
	if (content[0] == '?')
		return (ft_strdup("?"));
	while (content[len] != '\0' && ft_isalpha(content[len]))
		len++;
	var_name = ft_malloc((len + 1) * sizeof(char));
	i = 0;
	while (content[i] != '\0' && ft_isalpha(content[i]))
	{
		var_name[i] = content[i];
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}

char	*get_var_value(char *var_name)
{
	char	*value;

	if (var_name == NULL)
		return (NULL);
	else if (*var_name == '\0')
		return (ft_strdup("$"));
	else if (*var_name == '?')
		return (ft_itoa(*ft_exit_code()));
	value = ft_getenv(var_name);
	if (value == NULL)
		return (ft_strdup(""));
	else
		return (value);
}

size_t	get_expand_len(char *content)
{
	char	*var_name;
	size_t	size;
	size_t	sub_size;
	size_t	i;
	int		is_in_squote;

	is_in_squote = 0;
	if (content == NULL)
		return (0);
	i = 0;
	sub_size = 0;
	size = 0;
	while (content[i])
	{
		if (content[i] == '\'')
			is_in_squote = !is_in_squote;
		else if (!is_in_squote && content[i] == '$')
		{
			var_name = get_var_name(&content[i]);
			size = size + ft_strlen(get_var_value(var_name));
			sub_size = sub_size + (1 + ft_strlen(var_name));
		}
		i++;
	}
	return ((i - sub_size) + size);
}

void	set_to_buffer(char *buffer, size_t *buff_pos, char *src)
{
	size_t	i;

	if (src == NULL || buffer == NULL)
		return ;
	i = 0;
	while (src[i])
	{
		buffer[*buff_pos] = src[i];
		i++;
		(*buff_pos)++;
	}
}

int	handle_expansion(char *word, size_t *i, t_buffer *buffer)
{
	char	*var_name;
	char	*var_value;

	var_name = get_var_name(&word[*i]);
	var_value = get_var_value(var_name);
	set_to_buffer(buffer->buffer, &buffer->pos, var_value);
	*i = *i + 1 + ft_strlen(var_name);
	return (1);
}
