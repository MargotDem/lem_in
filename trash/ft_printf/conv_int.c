/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:03:31 by briffard          #+#    #+#             */
/*   Updated: 2022/05/30 15:22:00 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	format_int(t_parameter *li, int number);
int			format_char(t_parameter *option, char c);
static int	formaint(int number, t_parameter *option);
int			set_negatif(int number, t_parameter *option);

int	set_negatif(int number, t_parameter *option)
{
	number *= -1;
	option->flags = option->flags | F_NEGATIF;
	if (option->flags & F_PLUS)
		option->flags = option->flags ^ F_PLUS;
	return (number);
}

static int	format_int(t_parameter *option, int number)
{
	char	*dest;
	int		size;

	size = 0;
	if (number < 0)
		number = set_negatif(number, option);
	if (number == 0 && option->dot && option->pre == 0)
	{
		if (option->flags & F_HASHTAG)
				option->flags = option->flags ^ F_HASHTAG;
		return (print_int(option, ""));
	}
	dest = ft_l_itoa(ft_abs_int(number));
	size += print_int(option, dest);
	ft_memdel((void *)&dest);
	return (size);
}

int	format_char(t_parameter *option, char c)
{
	int	size;

	size = 0;
	size += print_width(option, 1);
	size += print_char(c);
	if (option->flags & F_MINUS)
		size += align_right(size, option->width);
	return (size);
}

static int	formaint(int number, t_parameter *option)
{
	if (number > 0)
		return (print_str("true", ft_strlen("true"), option));
	return (print_str("false", ft_strlen("false"), option));
}

/*
**Receive va_arg as int and print a char
*/
int	conv_to_int(t_parameter *option, va_list ap)
{
	if (option->conv == 'c')
		return (format_char(option, va_arg(ap, int)));
	else if (option->conv == 't')
		return (formaint(va_arg(ap, int), option));
	else if (option->flags & F_MOD)
		return (dispatch_to_intsizeprefix(option, ap));
	else
		return (format_int(option, va_arg(ap, int)));
}
