/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sizePrefix_for_flag_d.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 08:15:55 by briffard          #+#    #+#             */
/*   Updated: 2022/05/30 15:22:00 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	char_to_arr(t_parameter *option, char number)
{
	char	*temp;
	int		size;

	size = 0;
	if (number == 0 && option->dot && option->pre == 0)
	{
		if (option->flags & F_HASHTAG)
				option->flags = option->flags ^ F_HASHTAG;
		return (print_int(option, ""));
	}
	if (number < 0)
		number = set_negatif(number, option);
	temp = ft_itoa(ft_abs_int(number));
	size = print_int(option, temp);
	ft_memdel((void *) &temp);
	return (size);
}

int	short_int_to_arr(t_parameter *option, short int number)
{
	char	*temp;
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
	temp = ft_itoa(ft_abs_int(number));
	size = print_int(option, temp);
	ft_memdel((void *) &temp);
	return (size);
}

int	ll_int_to_arr(t_parameter *option, long long number)
{
	char	*temp;
	int		size;

	if (number < 0)
	{
		number *= -1;
		option->flags = option->flags | F_NEGATIF;
	}
	if (number == 0 && option->dot && option->pre == 0)
	{
		if (option->flags & F_HASHTAG)
				option->flags = option->flags ^ F_HASHTAG;
		return (print_int(option, ""));
	}
	size = 0;
	temp = ft_uitoa_base(number, 10);
	size = print_int(option, temp);
	ft_memdel((void *) &temp);
	return (size);
}

int	dispatch_to_intsizeprefix(t_parameter *option, va_list ap)
{
	if (!ft_strcmp(option->sizeprefix, "ll"))
		return (ll_int_to_arr(option, va_arg(ap, long long)));
	else if (!ft_strcmp(option->sizeprefix, "l"))
		return (ll_int_to_arr(option, va_arg(ap, long)));
	else if (!ft_strcmp(option->sizeprefix, "h"))
		return (short_int_to_arr(option, (short)va_arg(ap, int)));
	else if (!ft_strcmp(option->sizeprefix, "hh"))
		return (char_to_arr(option, (char)va_arg(ap, int)));
	else if (!ft_strcmp(option->sizeprefix, "z"))
		return (ll_int_to_arr(option, va_arg(ap, long long)));
	return (-1);
}
