/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_funct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 09:16:48 by briffard          #+#    #+#             */
/*   Updated: 2022/05/06 09:14:47 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			skip(char *str);
int			isnot_sizeprefix(char *str);
int			define_base(t_parameter *option);
int			isnot_precision(int c);
long double	set_dbl_negtif(long double number, t_parameter *option);

long double	set_dbl_negtif(long double number, t_parameter *option)
{
	if (ft_isdoubleneg(number))
	{
		number *= -1;
		option->flags = option->flags | F_NEGATIF;
		if (option->flags & F_PLUS)
			option->flags = option->flags ^ F_PLUS;
		return (number);
	}
	return (number);
}

int	define_base(t_parameter *option)
{
	if (option->conv == 'x' || option->conv == 'X' || option->conv == 'p')
		return (16);
	if (option->conv == 'o')
		return (8);
	return (10);
}

int	skip(char *str)
{
	int		index;

	index = 0;
	while (str[index] >= '0' && str[index] <= '9')
		index++;
	return (index);
}

int	isnot_sizeprefix(char *str)
{
	if ((str[0] == 'l' || str[0] == 'h' || str[0] == 'L' || str[0] == 'z') && \
	!checkparams(str[1]))
		return (0);
	if (str[0] == 'l' && str[1] == 'l' && !checkparams(str[2]))
		return (0);
	if (str[0] == 'h' && str[1] == 'h' && !checkparams(str[2]))
		return (0);
	return (1);
}

int	isnot_precision(int c)
{
	if (c == '.')
		return (0);
	if (c == '*')
		return (0);
	return (1);
}
