/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 12:26:18 by briffard          #+#    #+#             */
/*   Updated: 2022/05/06 08:39:14 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_precision(int start, t_parameter *option, char *str);
void	set_length(t_parameter *option, char *str);
int		print_int(t_parameter *option, char *str);
void	adjust_flags(t_parameter *option, char *str);
void	set_precision(t_parameter *option, char *str);

int	print_precision(int start, t_parameter *option, char *str)
{
	int	size;

	size = 0;
	while (start < (option->pre - (int)ft_strlen(str)) && option->conv != 'f')
	{
		size += print_char('0');
		start++;
	}
	return (size);
}

void	adjust_flags(t_parameter *option, char *str)
{
	(void)str;
	if (option->flags & F_ZERO && (option->conv != 'f') && \
	option->pre > 0)
		option->flags = option->flags ^ F_ZERO;
}

void	set_length(t_parameter *option, char *str)
{
	int	to_remove;

	to_remove = 0;
	if ((option->flags & F_HASHTAG && option->conv != 'o') || \
	(option->flags & F_HASHTAG && option->conv == 'o' && \
	option->pre <= (int)ft_numlength(ft_atoi(str))))
		to_remove += add_character_f_hashtag(option);
	if ((option->flags & F_NEGATIF || option->flags & F_PLUS) && \
	option->width >= option->pre)
		to_remove += 1;
	if (option->pre > option->width && option->conv != 'f')
		option->width = 0;
	option->length = (option->width - to_remove) - option->pre;
	if (option->length < 0)
		option->length = 0;
}

void	set_precision(t_parameter *option, char *str)
{
	if (option->pre < (int)ft_strlen(str) && option->conv != 'f')
		option->pre = (int)ft_strlen(str);
	if (option->conv == 'f' && option->pre > 0)
	{
		if (ft_numlength(ft_atoi(str)))
			option->pre += (int)ft_numlength(ft_atoi(str)) + 1;
		else
			option->pre += 2;
	}
	if (option->conv == 'f' && option->pre == 0)
	{
		if (ft_numlength(ft_atoi(str)) == 0)
			option->pre += 1;
		else
			option->pre += (int)ft_numlength(ft_atoi(str));
		option->adddot = 1;
	}
}

int	print_int(t_parameter *option, char *str)
{
	int	size;

	size = 0;
	adjust_flags(option, str);
	set_precision(option, str);
	set_length(option, str);
	if (option->flags & F_MINUS)
		return (align(str, option));
	if (option->flags & F_SPACE && option->width == 0 && \
	!(option->flags & F_NEGATIF))
	{
		size += print_char(' ');
		option->length -= 1;
	}
	if (option->flags & F_ZERO)
		size += set_zero(option, str);
	else
		size += set_space(option, str);
	size += print_precision(0, option, str);
	if (!str)
		size += print_char('0');
	else
		size += print_str(str, (int)ft_strlen(str), option);
	return (size);
}
