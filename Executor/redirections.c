/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-el- <aben-el-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:29:33 by aben-el-          #+#    #+#             */
/*   Updated: 2025/08/15 20:05:40 by aben-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	rd_out(t_list *redir)
{
	int	fd;

	fd = open(redir->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_print_error("msh : open : %s : %s\n",
			redir->content, strerror(errno));
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		perror("dup2");
		return (-1);
	}
	close(fd);
	return (0);
}

static int	rd_append(t_list *redir)
{
	int	fd;

	fd = open(redir->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_print_error("msh : open : %s : %s\n",
			redir->content, strerror(errno));
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		perror("dup2");
		return (-1);
	}
	close(fd);
	return (0);
}

static int	rd_in(t_list *redir)
{
	int	fd;

	fd = open(redir->content, O_RDONLY);
	if (fd == -1)
	{
		ft_print_error("msh : open : %s : %s\n",
			redir->content, strerror(errno));
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		perror("dup2");
		return (-1);
	}
	close(fd);
	return (0);
}

static int	rd_heredoc(t_list *redir)
{
	int	fd;

	fd = open(redir->content, O_RDONLY);
	if (fd == -1)
	{
		ft_print_error("msh : open : %s : %s\n",
			redir->content, strerror(errno));
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		perror("dup2");
		return (-1);
	}
	close(fd);
	return (0);
}

int	handel_redirections(t_command *cmd)
{
	t_list	*redir;
	t_list	*new_list;

	redir = cmd->redirects;
	while (redir)
	{
		new_list = expand_word(redir->content, 1);
		if (ft_t_lst_size(new_list) != 1)
			return (ft_print_error("minishell: %s: ambiguous redirect\n",
					redir->content), -1);
		else
			redir->content = new_list->content;
		if (redir->type == REDIRECT_OUT && rd_out(redir) == -1)
			return (-1);
		else if (redir->type == REDIRECT_IN && rd_in(redir) == -1)
			return (-1);
		else if (redir->type == REDIRECT_APPEND && rd_append(redir) == -1)
			return (-1);
		else if (redir->type == REDIRECT_HEREDOC && rd_heredoc(redir) == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}
