/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 04:48:30 by aazounda          #+#    #+#             */
/*   Updated: 2025/08/16 13:19:28 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*create_random_name(void)
{
	char	buffer[32];
	int		pos;
	int		fd;
	char	c;

	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
		return (perror("open_/dev/random"), NULL);
	pos = 0;
	while (pos < 32)
	{
		if (read(fd, &c, 1) <= 0)
			return (close(fd), NULL);
		if (c && ft_isalnum(c))
			buffer[pos++] = c;
	}
	close(fd);
	buffer[pos] = '\0';
	return (ft_strjoin("/var/tmp/", buffer));
}

/* you can make fuction, just to check delemiter, without mallocation */
static char	*get_delemiter(char *content)
{
	char	*buffer;
	size_t	i;
	size_t	j;
	int		quote;

	buffer = ft_malloc((ft_strlen(content) + 1) * sizeof(char));
	i = 0;
	j = 0;
	while (content[i])
	{
		if (content[i] == '\"' || content[i] == '\'')
		{
			quote = content[i];
			i++;
			while (content[i] && content[i] != quote)
				buffer[j++] = content[i++];
			i++;
		}
		else
			buffer[j++] = content[i++];
	}
	buffer[j] = '\0';
	return (buffer);
}

static void	heredoc_child_proccess(int fd, char *delemiter, int expand_f)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_print_error("msh: warning: here-document delimited \
by end-of-file (wanted `%s')\n", delemiter);
			break ;
		}
		collector(COLLECT, line);
		if (ft_strcmp(delemiter, line) == 0)
			break ;
		if (expand_f)
			ft_putstr_fd(expand_in_heredoc(line), fd);
		else
			ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
	}
	ft_exit_clean(EXIT_SUCCESS);
}

static int	execute_heredoc(int fd, char *delemiter, int expand_f)
{
	int		status;
	pid_t	pid;

	setup_ignore_signals();
	pid = fork();
	if (pid < 0)
	{
		setup_signals(0);
		return (1);
	}
	else if (pid == 0)
	{
		setup_child_signals(1);
		heredoc_child_proccess(fd, delemiter, expand_f);
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		handle_sigexit_child(WTERMSIG(status));
	setup_signals(0);
	return (ft_exit_status(status));
}

int	handle_heredoc(char **content)
{
	char	*tmpfile;
	int		fd;
	int		exit_code;
	int		expand_f;

	tmpfile = create_random_name();
	if (tmpfile == NULL)
		return (1);
	fd = open(tmpfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
	{
		perror("here_doc_open");
		return (1);
	}
	collect_fds(COLLECT_FD, fd);
	expand_f = !(ft_strchr(*content, '\'') || ft_strchr(*content, '"'));
	exit_code = execute_heredoc(fd, get_delemiter(*content), expand_f);
	*content = tmpfile;
	tmpfiles_collector(COLLECT_TMPFILE, tmpfile);
	return (exit_code);
}
