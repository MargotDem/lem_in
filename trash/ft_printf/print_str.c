/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 12:29:25 by briffard          #+#    #+#             */
/*   Updated: 2022/05/05 16:02:05 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_width(t_parameter *option, int length);
int	print_str(const char *str, int length, t_parameter *option);
int	print_char(char c);
int	align_right(int start, int length);

int	align_right(int start, int length)
{
	int	size;

	size = 0;
	while (start < length)
	{
		size += print_char(' ');
		start++;
	}
	return (size);
}

/*
**print a char to stdout
*/
int	print_char(char c)
{
	write(1, &c, 1);
	return (1);
}

/*
**print a char* until pre
*/
int	print_str(const char *str, int length, t_parameter *option)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	while (i < length)
	{
		size += print_char(str[i]);
		i++;
	}
	if (option->flags & F_HASHTAG && option->conv == 'f' && option->adddot)
		size += print_char('.');
	return (size);
}

/*
** print width parameter for flag c & s
*/
int	print_width(t_parameter *option, int length)
{
	int	size;

	size = 0;
	while (size < (option->width - length) && option->flags ^ F_MINUS)
	{
		if (option->flags & F_ZERO)
			size += print_char('0');
		else
			size += print_char(' ');
	}
	return (size);
}
