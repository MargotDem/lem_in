/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_Flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 11:47:35 by briffard          #+#    #+#             */
/*   Updated: 2022/05/06 08:58:10 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_uchar	get_flag(char c);

static t_uchar	get_flag(char c)
{
	if (c == '#')
		return (F_HASHTAG);
	else if (c == '+')
		return (F_PLUS);
	else if (c == '-')
		return (F_MINUS);
	else if (c == '0')
		return (F_ZERO);
	else
		return (F_SPACE);
}

t_parameter	*handle_flag(char *str, t_parameter *li)
{
	int	i;

	li->flags = 0x00;
	i = 0;
	while (str[i] == '#' || str[i] == '0' || str[i] == '+' || str[i] == '-' \
	|| str[i] == ' ')
	{
		li->flags = li->flags | get_flag(str[i]);
		i++;
	}
	li->char_to_skip = i;
	return (li);
}

t_parameter	*handle_width(char *str, t_parameter *li, va_list ap)
{
	if (str[0] == '*' && !(ft_isdigit(str[1])))
	{
		li->width = va_arg(ap, int);
		li->char_to_skip += 1;
		if (li->width < 0)
		{
			li->flags = li->flags | F_MINUS;
			li->width = ft_abs_int(li->width);
		}
	}
	else
	{
		if (str[0] == '*' && ft_isdigit(str[1]))
		{
			li->width = va_arg(ap, int);
			li->width = ft_atoi(&str[1]);
			li->char_to_skip += skip(&str[1]) + 1;
		}
		else
		{
			li->width = ft_atoi(str);
			li->char_to_skip += skip(str);
		}
	}
	return (li);
}

t_parameter	*handle_precision(char *str, t_parameter *li, va_list ap)
{
	if (str[0] == '.')
	{
		li->dot = 1;
		if (str[1] == '*')
		{
			li->pre = va_arg(ap, int);
			li->char_to_skip += 2;
		}
		else
		{
			li->pre = ft_atoi(&str[1]);
			if (!li->pre && checkparams(str[1]) && str[1] != '0')
				li->error = 1;
			li->char_to_skip += skip(&str[1]) + 1;
		}	
	}
	else if (checkparams(str[0]) && isnot_sizeprefix(str))
		li->error = 1;
	return (li);
}

t_parameter	*handle_size_prefix(char *str, t_parameter *li)
{
	int	i;

	i = 0;
	ft_bzero(li->sizeprefix, 5);
	if (str[0] == 'l' || str[0] == 'h' || str[0] == 'L' || str[0] == 'z')
	{
		li->sizeprefix[i] = str[i];
		i += 1;
		while (str[i - 1] == str[i] && i < 2)
		{
			li->sizeprefix[i] = str[i];
			i++;
		}
		li->sizeprefix[i] = '\0';
		while (i <= 5)
			li->sizeprefix[i++] = '\0';
		li->char_to_skip += ft_strlen(li->sizeprefix);
		li->flags = li->flags | F_MOD;
	}
	return (li);
}
