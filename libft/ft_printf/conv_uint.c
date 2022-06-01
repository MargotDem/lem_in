/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_uint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:05:21 by briffard          #+#    #+#             */
/*   Updated: 2022/05/03 14:48:39 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	format_uint(t_parameter *option, unsigned int number);
int	u_ll_itoa(t_parameter *option, unsigned long long int number);

int	if_zero(t_parameter *option, unsigned long long int number)
{
	if (!(option->flags & F_MINUS))
	{
		if (option->flags & F_HASHTAG && option->conv != 'o')
				option->flags = option->flags ^ F_HASHTAG;
		if (option->conv == 'o' && option->width)
			return (print_int(option, " "));
		return (print_int(option, ""));
	}
	else if (option->flags & F_MINUS)
	{
		if (option->flags & F_HASHTAG && option->conv != 'o')
				option->flags = option->flags ^ F_HASHTAG;
		if (option->conv == 'o' && option->width && option->pre)
			return (print_int(option, "0"));
		return (print_int(option, ""));
	}
	return (number);
}

int	u_ll_itoa(t_parameter *option, unsigned long long int number)
{
	char	*temp;
	int		size;

	size = 0;
	if (number == 0 && option->dot && option->pre == 0)
	{
		if (option->flags & F_HASHTAG && option->conv != 'o')
			option->flags = option->flags ^ F_HASHTAG;
		if (option->conv == 'o' && option->width)
			return (print_int(option, " "));
		return (print_int(option, ""));
	}
	if (number == 0 && option->flags & F_HASHTAG && option->conv == 'x')
		option->flags = option->flags ^ F_HASHTAG;
	temp = ft_uitoa_base(number, define_base(option));
	if (!temp)
		exit(EXIT_FAILURE);
	if (option->upper)
		ft_strtoupper(temp);
	size += print_int(option, temp);
	ft_memdel((void *)&temp);
	return (size);
}

int	format_uint(t_parameter *option, unsigned int number)
{
	char	*str;
	int		size;

	size = 0;
	if (number == 0 && option->dot && option->pre == 0)
		return (if_zero(option, number));
	if (number == 0 && option->flags & F_HASHTAG && option->conv == 'x')
		option->flags = option->flags ^ F_HASHTAG;
	str = ft_uitoa_base(number, define_base(option));
	if (!str)
		exit(EXIT_FAILURE);
	if (option->upper)
		ft_strtoupper(str);
	size += print_int(option, str);
	ft_memdel((void *)&str);
	return (size);
}

int	conv_to_uint(t_parameter *option, va_list ap)
{
	if (!ft_strcmp(option->sizeprefix, "ll"))
		return (u_ll_itoa(option, va_arg(ap, unsigned long long)));
	else if (!ft_strcmp(option->sizeprefix, "l"))
		return (u_ll_itoa(option, va_arg(ap, unsigned long)));
	else if (!ft_strcmp(option->sizeprefix, "h"))
		return (u_ll_itoa(option, (unsigned short)va_arg(ap, int)));
	else if (!ft_strcmp(option->sizeprefix, "hh"))
		return (u_ll_itoa(option, (unsigned char)va_arg(ap, int)));
	else if (!ft_strcmp(option->sizeprefix, "z"))
		return (u_ll_itoa(option, va_arg(ap, unsigned long)));
	else
		return (format_uint(option, va_arg(ap, unsigned int)));
}
