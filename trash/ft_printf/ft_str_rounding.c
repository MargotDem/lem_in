/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_rounding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 10:00:18 by briffard          #+#    #+#             */
/*   Updated: 2022/05/04 11:03:51 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*check_for_zero(char *number, int last_index)
{
	if (last_index == 0)
		number = ft_strjoin_replace("1", number, 1);
	else
		number[last_index - 1] = number[last_index - 1] + 1;
	return (number);
}

char	*formatrounding(char *number, int last_index)
{
	while (last_index >= 0)
	{
		if (number[last_index] == ':')
		{
			number[last_index] = '0';
			if (number[last_index - 1] == '.')
				last_index--;
			number = check_for_zero(number, last_index);
		}
		if ((number[0] == ':' || number[0] == '.') && (int)last_index == 0)
		{
			number[0] = '0';
			number = ft_strjoin_replace("1", number, 1);
		}
		last_index--;
	}
	return (number);
}

char	*round2(char *str, int fpart, long double number, t_parameter *li)
{
	int	last_index;

	last_index = (int)ft_strlen(str) - 1;
	if (li->pre == 0)
	{
		if (number > 0.50)
			str[last_index] = str[last_index] + 1;
	}
	else if (li->pre == 1)
	{
		if ((fpart >= 5) && number != 0.25)
			str[last_index] = str[last_index] + 1;
		str = formatrounding(str, last_index);
	}
	return (str);
}

char	*rounding(char *number, int fpart, int last_index, t_parameter *option)
{
	if (fpart >= 5 && option->pre > 0)
	{
		if (!(option->flags & F_NEGATIF))
			number[last_index] = number[last_index] + 1;
		else if (option->flags & F_NEGATIF)
		{
			if (fpart > 5 || (fpart == 5 && ft_atoi(number) == 0))
				number[last_index] = number[last_index] + 1;
		}
	}
	else if (option->pre == 0)
	{
		if (fpart > 5)
			number[last_index] = number[last_index] + 1;
		if (fpart == 5)
			if ((number[last_index] + '0') % 2 == 1)
				number[last_index] = number[last_index] + 1;
	}
	number = formatrounding(number, last_index);
	return (number);
}
