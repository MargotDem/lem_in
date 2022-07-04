/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print_int2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:53:14 by briffard          #+#    #+#             */
/*   Updated: 2022/05/03 16:07:27 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_sign(t_parameter *option);
int		print_0x(t_parameter *option, char *str);

int	print_0x(t_parameter *option, char *str)
{
	int	size;

	size = 0;
	if (option->conv == 'x' || option->conv == 'p')
	{
		if (option->upper)
			size += print_str("0X", ft_strlen("0X"), option);
		else
			size += print_str("0x", ft_strlen("0x"), option);
		option->flags = option->flags ^ F_HASHTAG;
	}
	else if (option->conv == 'o' && \
	option->pre <= (int)ft_numlength(ft_atoi(str)))
	{
		size += print_char('0');
		option->flags = option->flags ^ F_HASHTAG;
	}
	return (size);
}

int	print_sign(t_parameter *option)
{
	int	size;

	size = 0;
	if (option->flags & F_NEGATIF)
		size += print_char('-');
	else if (option->flags & F_PLUS)
		size += print_char ('+');
	return (size);
}
