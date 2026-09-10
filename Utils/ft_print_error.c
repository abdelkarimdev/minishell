/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:46:23 by aazounda          #+#    #+#             */
/*   Updated: 2025/08/16 11:32:53 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*print_type(const char *format, va_list args)
{
	char	*str;

	str = NULL;
	if (*(format + 1) == 's')
		str = ft_strdup(va_arg(args, char *));
	return (str);
}

void	ft_print_error(const char *format, ...)
{
	va_list	args;
	char	*line;
	char	str[2];

	line = NULL;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			line = ft_strjoin(line, print_type(format, args));
			format++;
		}
		else
		{
			str[0] = *format;
			str[1] = '\0';
			line = ft_strjoin(line, str);
		}
		format++;
	}
	write(STDERR_FILENO, line, ft_strlen(line));
	va_end(args);
}
