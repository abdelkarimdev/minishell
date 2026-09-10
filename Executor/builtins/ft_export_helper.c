/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 10:39:13 by aben-el-          #+#    #+#             */
/*   Updated: 2025/08/14 08:39:00 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strlen_key(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

size_t	get_len(char *s1, char *s2)
{
	size_t	len;

	len = 0;
	if (ft_strlen_key(s1) > ft_strlen_key(s2))
		len = ft_strlen_key(s2);
	else
		len = ft_strlen_key(s1);
	return (len);
}

void	ft_swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

int	check_identifier(char *var)
{
	size_t	i;

	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	i = 1;
	while (var[i])
	{
		if (var[i] == '=')
			break ;
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
