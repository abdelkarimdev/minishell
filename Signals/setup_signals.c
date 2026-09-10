/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:01:08 by aazounda          #+#    #+#             */
/*   Updated: 2025/08/15 22:16:52 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setup_signals(int set_prev)
{
	__sighandler_t	sigint_prev;
	__sighandler_t	sigquit_prev;

	sigint_prev = signal(SIGINT, sighandler_interactive);
	sigquit_prev = signal(SIGQUIT, SIG_IGN);
	if (set_prev)
	{
		prev_handler(SET_SIGINT_HND, sigint_prev);
		prev_handler(SET_SIGQUIT_HND, sigquit_prev);
	}
}

void	setup_ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_child_signals(int is_heredoc)
{
	if (is_heredoc)
	{
		signal(SIGINT, heredoc_sighandler);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, prev_handler(GET_SIGINT_HND, NULL));
		signal(SIGQUIT, prev_handler(GET_SIGQUIT_HND, NULL));
	}
}
