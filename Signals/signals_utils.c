/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:04:18 by aazounda          #+#    #+#             */
/*   Updated: 2025/08/15 22:19:10 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sighandler_interactive(int sig)
{
	if (sig == SIGINT)
	{
		*ft_exit_code() = 130;
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sigexit_child(int sig)
{
	if (sig == SIGINT)
		write(2, "\n", 1);
	if (sig == SIGQUIT)
		write(2, "Quit (core dumped)\n", 19);
}

void	heredoc_sighandler(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		ft_exit_clean(130);
	}
}

__sighandler_t	prev_handler(int option, __sighandler_t handler)
{
	static __sighandler_t	sigint_prev_handler;
	static __sighandler_t	sigquit_prev_handler;

	if (option == SET_SIGINT_HND)
		sigint_prev_handler = handler;
	else if (option == SET_SIGQUIT_HND)
		sigquit_prev_handler = handler;
	else if (option == GET_SIGINT_HND)
		return (sigint_prev_handler);
	else if (option == GET_SIGQUIT_HND)
		return (sigquit_prev_handler);
	return (NULL);
}
