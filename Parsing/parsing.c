/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 03:18:26 by aazounda          #+#    #+#             */
/*   Updated: 2025/08/16 13:22:15 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	set_types(t_list *tokens)
{
	t_list	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "|", ft_strlen(tmp->content)) == 0)
			tmp->type = TOKEN_PIPE;
		else if (ft_strncmp(tmp->content, "<", ft_strlen(tmp->content)) == 0)
			tmp->type = TOKEN_REDIRECT_IN;
		else if (ft_strncmp(tmp->content, ">", ft_strlen(tmp->content)) == 0)
			tmp->type = TOKEN_REDIRECT_OUT;
		else if (ft_strncmp(tmp->content, ">>", ft_strlen(tmp->content)) == 0)
			tmp->type = TOKEN_REDIRECT_APPEND;
		else if (ft_strncmp(tmp->content, "<<", ft_strlen(tmp->content)) == 0)
			tmp->type = TOKEN_HEREDOC;
		else
			tmp->type = TOKEN_WORD;
		tmp = tmp->next;
	}
}

static int	parse_redirects(t_list *current, t_list **redirects)
{
	int	exit_code;

	if (current->next == NULL)
		return (ft_print_error("msh: syntax error near \
unexpected token `newline'\n"), 2);
	if (current->next->type != TOKEN_WORD)
		return (ft_print_error("msh: syntax error near unexpected token `%s'\n",
				current->next->content), 2);
	else
	{
		if (current->type == TOKEN_HEREDOC)
		{
			exit_code = handle_heredoc(&current->next->content);
			if (exit_code != EXIT_SUCCESS)
				return (exit_code);
		}
		add_node(redirects, current->next->content, current->type);
	}
	return (EXIT_SUCCESS);
}

static int	parse_single_command(t_list *current, t_command **commands)
{
	t_list	*args;
	t_list	*redirects;
	int		exit_code;

	args = NULL;
	redirects = NULL;
	while (current != NULL && current->type != TOKEN_PIPE)
	{
		if (current->type == TOKEN_REDIRECT_IN
			|| current->type == TOKEN_REDIRECT_OUT
			|| current->type == TOKEN_REDIRECT_APPEND
			|| current->type == TOKEN_HEREDOC)
		{
			exit_code = parse_redirects(current, &redirects);
			if (exit_code != EXIT_SUCCESS)
				return (exit_code);
			current = current->next;
		}
		else
			add_node(&args, current->content, TOKEN_WORD);
		if (current)
			current = current->next;
	}
	add_command(commands, args, redirects);
	return (EXIT_SUCCESS);
}

static int	parse_pipeline(t_list **tokens, t_command **commands)
{
	t_list	*current;
	int		exit_code;

	current = *tokens;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
			return (ft_print_error("msh: syntax error \
near unexpected token `|'\n"), 2);
		exit_code = parse_single_command(current, commands);
		if (exit_code != EXIT_SUCCESS)
			return (exit_code);
		while (current && current->type != TOKEN_PIPE)
			current = current->next;
		if (current && current->type == TOKEN_PIPE && current->next == NULL)
			return (ft_print_error("msh: syntax error\n"), 2);
		if (current)
			current = current->next;
	}
	return (EXIT_SUCCESS);
}

int	parsing(char *input, t_command **commands)
{
	t_list	*tokens;
	int		exit_code;

	exit_code = EXIT_SUCCESS;
	tokens = NULL;
	exit_code = tokenizer(input, &tokens);
	if (tokens == NULL)
		return (-1);
	if (exit_code != EXIT_SUCCESS)
	{
		*ft_exit_code() = exit_code;
		return (-1);
	}
	set_types(tokens);
	exit_code = parse_pipeline(&tokens, commands);
	if (exit_code != EXIT_SUCCESS)
	{
		*ft_exit_code() = exit_code;
		return (-1);
	}
	return (0);
}
