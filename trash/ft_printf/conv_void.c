/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_void.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 11:54:34 by briffard          #+#    #+#             */
/*   Updated: 2022/05/05 09:47:36 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	format_binary(t_parameter *option, void const *ptr);

static int	format_binary(t_parameter *option, void const *ptr)
{
	int	size;

	(void)option;
	size = 0;
	size += ft_printbits(&ptr, sizeof(ptr));
	return (size);
}

int	conv_to_void(t_parameter *li, va_list ap)
{
	return (format_binary(li, va_arg(ap, void *)));
}
