/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-el- <aben-el-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 09:28:28 by aben-el-          #+#    #+#             */
/*   Updated: 2025/08/14 09:16:20 by aben-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_number(const char *nptr, long *num)
{
	int			sign;
	__int128_t	result;

	sign = 1;
	result = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
	{
		nptr++;
	}
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = sign * (-1);
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - 48);
		if (result > LONG_MAX)
			return (-1);
		nptr++;
	}
	*num = (long)(result * sign);
	return (1);
}

void	check_args_exit(t_list *cmd)
{
	long	exit_value;

	if (check_arg(cmd->content) == 0
		|| get_number(cmd->content, &exit_value) == -1)
	{
		ft_print_error("exit : %s: numeric argument required\n", cmd->content);
		ft_exit_clean(2);
	}
	else
	{
		exit_value = exit_value % 256;
		printf("exit\n");
		ft_exit_clean(exit_value);
	}
}

int	ft_exit(t_list *cmd)
{
	if (cmd)
	{
		if (check_arg(cmd->content) == 0)
		{
			ft_print_error("exit : %s: numeric argument required\n",
				cmd->content);
			ft_exit_clean(2);
		}
		if (cmd->next)
		{
			printf("exit\n");
			ft_print_error("minishell : exit: too many arguments\n");
			return (1);
		}
		else
			check_args_exit(cmd);
	}
	ft_exit_clean(*ft_exit_code());
	return (0);
}
