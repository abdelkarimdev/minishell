/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:09:57 by aazounda          #+#    #+#             */
/*   Updated: 2025/08/14 08:55:46 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	take_in_squotes(char *str, size_t *i, t_buffer *buffer)
{
	int	is_empty;

	is_empty = 0;
	(*i)++;
	while (str[*i] && str[*i] != '\'')
	{
		is_empty = 1;
		buffer->buffer[buffer->pos++] = str[(*i)++];
	}
	(*i)++;
	if (is_empty == 0 && buffer->has_empty_str != 1)
		buffer->has_empty_str = 1;
	return (1);
}

static int	take_in_dquotes(char *str, size_t *i, t_buffer *buffer)
{
	char	*var_name;
	int		is_empty;

	is_empty = 0;
	(*i)++;
	while (str[*i] != '\"')
	{
		is_empty = 1;
		if (str[*i] == '$')
		{
			var_name = get_var_name(&str[*i]);
			set_to_buffer(buffer->buffer, &buffer->pos,
				get_var_value(var_name));
			(*i) = (*i) + 1 + ft_strlen(var_name);
		}
		else
			buffer->buffer[buffer->pos++] = str[(*i)++];
	}
	(*i)++;
	if (is_empty == 0 && buffer->has_empty_str != 1)
		buffer->has_empty_str = 1;
	return (1);
}

static void	handle_split_expansion(char *word, size_t *i, t_buffer *buffer,
		t_list **words)
{
	char	*var_name;
	char	*var_value;

	var_name = get_var_name(&word[*i]);
	var_value = get_var_value(var_name);
	while (*var_value)
	{
		if (is_whitespace(*var_value))
		{
			if (buffer->pos > 0 || buffer->has_empty_str)
			{
				buffer->buffer[buffer->pos] = '\0';
				add_node(words, ft_strdup(buffer->buffer), 0);
				buffer->pos = 0;
			}
			while (is_whitespace(*var_value))
				var_value++;
		}
		else
		{
			buffer->buffer[buffer->pos++] = *var_value;
			var_value++;
		}
	}
	*i = *i + 1 + ft_strlen(var_name);
}

static void	init(size_t *i, t_buffer *buffer, t_list **words, size_t expand_len)
{
	buffer->buffer = ft_malloc((expand_len + 1) * sizeof(char));
	*words = NULL;
	*i = 0;
	buffer->pos = 0;
	buffer->has_empty_str = 0;
}

t_list	*expand_word(char *str, int split_flag)
{
	t_list		*words;
	t_buffer	buffer;
	size_t		i;

	init(&i, &buffer, &words, get_expand_len(str));
	while (str[i])
	{
		if (str[i] == '\'')
			take_in_squotes(str, &i, &buffer);
		else if (str[i] == '\"')
			take_in_dquotes(str, &i, &buffer);
		else if (str[i] == '$' && split_flag)
			handle_split_expansion(str, &i, &buffer, &words);
		else if (str[i] == '$')
			handle_expansion(str, &i, &buffer);
		else
			buffer.buffer[buffer.pos++] = str[i++];
	}
	if (buffer.pos > 0 || buffer.has_empty_str)
	{
		buffer.buffer[buffer.pos] = '\0';
		add_node(&words, ft_strdup(buffer.buffer), 0);
	}
	return (words);
}
