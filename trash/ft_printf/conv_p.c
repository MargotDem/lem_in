/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:06:06 by briffard          #+#    #+#             */
/*   Updated: 2022/05/13 08:13:00 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	format_ptr(t_parameter *option, unsigned long long int number);

static int	format_ptr(t_parameter *option, unsigned long long int number)
{
	char	*str;
	int		size;

	size = 0;
	if (number == 0 && option->dot && option->pre == 0)
		return (print_int(option, ""));
	str = ft_uitoa_base(number, define_base(option));
	if (!str)
		exit(EXIT_FAILURE);
	if (option->upper)
		ft_strtoupper(str);
	size += print_int(option, str);
	ft_memdel((void *) &str);
	return (size);
}

/*turn va_arg as ULL*/
int	conv_to_ptr(t_parameter *li, va_list ap)
{
	if (!(li->flags & F_HASHTAG))
		li->flags = li->flags | F_HASHTAG;
	return (format_ptr(li, va_arg(ap, unsigned long long int)));
}
