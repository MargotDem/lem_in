/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 12:38:24 by briffard          #+#    #+#             */
/*   Updated: 2022/05/05 16:01:21 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		add_character_f_hashatg(t_parameter *option);
int		set_space(t_parameter *option, char *str);
int		set_zero(t_parameter *option, char *str);
void	adjust_length(t_parameter *option, char *str, int to_remove);
int		align(char *str, t_parameter *option);

int	add_character_f_hashtag(t_parameter *option)
{
	if (option->conv == 'o' || (option->conv == 'f' && option->adddot))
		return (1);
	else if (option->conv == 'x' || option->conv == 'p')
		return (2);
	else
		return (0);
}

int	set_space(t_parameter *option, char *str)
{
	int	size;

	size = 0;
	if (option->length == 1)
	{
		size += print_char(' ');
		option->length -= 1;
	}
	while (size < option->length)
		size += print_char(' ');
	if (option->flags & F_HASHTAG)
		size += print_0x(option, str);
	if (option->flags & F_PLUS || option->flags & F_NEGATIF)
		size += print_sign(option);
	return (size);
}

int	set_zero(t_parameter *option, char *str)
{
	int	size;

	size = 0;
	if (option->flags & F_HASHTAG)
		size += print_0x(option, str);
	if (option->flags & F_SPACE && option->length >= 1 && \
	!(option->flags & F_NEGATIF))
	{
		size += print_char(' ');
		option->length -= 1;
	}
	if (option->flags & F_PLUS || option->flags & F_NEGATIF)
		size += print_sign(option);
	while (option->length > 0)
	{
		size += print_char('0');
		option->length -= 1;
	}
	return (size);
}

void	adjust_length(t_parameter *option, char *str, int to_remove)
{
	if (option->conv == 'f')
		option->pre += (ft_numlength(ft_atoi(str)) + 1);
	if (option->pre > option->width && option->conv != 'f')
		option->width = 0;
	else
	{
		option->length = (option->width - to_remove) - option->pre;
		if (option->length < 0)
			option->length = 0;
	}
	if (option->width == 0 && option->pre == (int)ft_strlen(str) && \
	option->flags & F_SPACE && (!(option->flags & F_NEGATIF) && \
	!(option->flags & F_PLUS)))
		option->length += 1;
	if (option->conv == 'u' && option->flags & F_HASHTAG && \
	option->width > option->pre)
		option->length += 2;
}

int	align(char *str, t_parameter *option)
{
	int	size;

	size = 0;
	if (option->flags & F_SPACE && (!(option->flags & F_NEGATIF) && \
	!(option->flags & F_PLUS)))
		size += print_char(' ');
	if (option->flags & F_HASHTAG)
		size += print_0x(option, str);
	if (option->flags & F_PLUS || option->flags & F_NEGATIF)
		size += print_sign(option);
	size += print_precision(0, option, str);
	size += print_str(str, (int)ft_strlen(str), option);
	while (size < option->width)
		size += print_char(' ');
	return (size);
}
