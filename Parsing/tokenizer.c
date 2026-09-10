/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:29:01 by aazounda          #+#    #+#             */
/*   Updated: 2025/08/12 19:52:45 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_meta_character(int c)
{
	return (c == '|' || c == '>' || c == '<');
}

static int	take_operator(const char *input, int *i, t_list **tokens)
{
	int		start;
	size_t	len;

	start = *i;
	if (input[*i] == '>' && input[(*i) + 1] == '>')
		*i = *i + 2;
	else if (input[*i] == '<' && input[(*i) + 1] == '<')
		*i = *i + 2;
	else
		*i = *i + 1;
	len = (*i) - start;
	if (len > 0)
		add_node(tokens, ft_substr(input, start, len), 2);
	return (EXIT_SUCCESS);
}

static int	take_word(const char *input, int *i, t_list **tokens)
{
	int	quote;
	int	start;

	start = *i;
	while (input[*i] != '\0' && !is_whitespace(input[*i])
		&& !is_meta_character(input[*i]))
	{
		if (input[*i] == '\"' || input[*i] == '\'')
		{
			quote = input[*i];
			(*i)++;
			while (input[*i] != quote)
			{
				if (input[*i] == '\0')
					return (ft_print_error("msh: unclosed quote\n"), 2);
				(*i)++;
			}
			(*i)++;
		}
		else
			(*i)++;
	}
	if (*i > start)
		add_node(tokens, ft_substr(input, start, (*i) - start), 1);
	return (EXIT_SUCCESS);
}

int	tokenizer(const char *input, t_list **tokens)
{
	int	i;
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	i = 0;
	while (input[i])
	{
		while (is_whitespace(input[i]))
			i++;
		if (is_meta_character(input[i]))
			exit_code = take_operator(input, &i, tokens);
		else if (input[i])
			exit_code = take_word(input, &i, tokens);
	}
	return (exit_code);
}
