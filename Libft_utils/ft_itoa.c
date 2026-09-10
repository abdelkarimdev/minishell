/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:05:00 by aazounda          #+#    #+#             */
/*   Updated: 2025/08/16 10:15:46 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	chars_counter(int nbr)
{
	int	count;

	count = 0;
	if (nbr == 0)
		count++;
	else if (nbr < 0)
		count++;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		count++;
	}
	return (count);
}

static char	*reverse(char *str)
{
	size_t	i;
	size_t	len;
	char	save;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		save = str[i];
		str[i] = str[len - 1];
		str[len - 1] = save;
		i++;
		len--;
	}
	return (str);
}

static unsigned int	get_abs(int nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

char	*ft_itoa(int nbr)
{
	char			*str;
	unsigned int	nb;
	int				size;
	int				i;

	size = chars_counter(nbr);
	str = (char *)malloc((size + 1) * sizeof(char));
	collector(0, str);
	i = 0;
	nb = get_abs(nbr);
	while (i < size - (nbr < 0))
	{
		str[i] = nb % 10 + 48;
		i++;
		nb = nb / 10;
	}
	if (nbr < 0)
		str[i++] = '-';
	str[i] = '\0';
	return (reverse(str));
}
