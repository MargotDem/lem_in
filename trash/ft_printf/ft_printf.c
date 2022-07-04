/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 08:24:41 by briffard          #+#    #+#             */
/*   Updated: 2022/05/30 15:21:41 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	dispatch(va_list ap, t_parameter *new);

/*
** Receive va_list and send to the right function
*/
static int	dispatch(va_list ap, t_parameter *new)
{
	if (new->conv == '%')
		return (format_char(new, '%'));
	else
		return (g_funcflagsarray[new->conv - 'a'](new, ap));
}

int	ft_printf(const char *format, ...)
{
	t_parameter	*option;
	va_list		ap;
	int			size;
	int			i;

	size = 0;
	i = 0;
	option = NULL;
	va_start(ap, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			option = init(&format[i], option, ap);
			if (option == NULL)
				return (error ("(Error founded.The output will be altered)\n"));
			size += dispatch(ap, option);
			i += option->size + 1;
		}
		else
			size += print_char(format[i++]);
	}
	va_end(ap);
	free(option);
	return (size);
}
