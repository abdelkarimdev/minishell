/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 04:51:54 by aazounda          #+#    #+#             */
/*   Updated: 2025/08/16 09:39:41 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_and_copyenv(void)
{
	environment_copy(SET, ft_envp(NULL));
	tmpfiles_collector(UNLINK_ALL, NULL);
	collector(CLEAR, NULL);
}

static int	parse(char *input, t_command **commands)
{
	int	error;

	error = parsing(input, commands);
	collect_fds(CLOSE_ALL, -1);
	if (error != -1)
		error = expand_cmds(*commands);
	return (error);
}

static void	shell_loop(char **_env)
{
	t_command	*commands;
	char		*input;

	while (1)
	{
		commands = NULL;
		if (environment_copy(GET, NULL))
			ft_envp(copy_envp(environment_copy(GET, NULL), CP));
		else
			ft_envp(copy_envp(_env, CP));
		input = readline("minishell$ ");
		if (!input)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			ft_exit_clean(*ft_exit_code());
		}
		collector(COLLECT, input);
		if (*input)
		{
			add_history(input);
			if (parse(input, &commands) != -1)
				*ft_exit_code() = executor(commands);
		}
		clean_and_copyenv();
	}
}

int	main(int _ac, char **_av, char **_env)
{
	(void)_ac;
	(void)_av;
	setup_signals(1);
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return (0);
	shell_loop(_env);
	return (0);
}
