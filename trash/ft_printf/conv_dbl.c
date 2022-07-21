/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_dbl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 09:18:48 by briffard          #+#    #+#             */
/*   Updated: 2022/05/13 08:10:44 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	format_dbl(t_parameter *option, long double number);
static int	getdigit(int pre, long double fpart);
char		*set_fpart(char *box, t_parameter *option, long double fpart);

static int	ft_isinf(long double x)
{
	if (x == -1.0 / 0.0)
		return (1);
	if (x == 1.0 / 0.0)
		return (1);
	return (0);
}

/*Return digit that you need for the rouding (pre + 1) */
static int	getdigit(int pre, long double fpart)
{
	int	i;

	i = 0;
	while (i < pre)
	{
		fpart = fpart * 10;
		fpart = fpart - (long long) fpart;
		i++;
	}
	return (fpart * 10);
}

/*ADD float part to the str*/
char	*set_fpart(char *box, t_parameter *option, long double fpart)
{
	int		i;

	box = ft_strnew(option->pre + 1);
	if (!box)
		exit (EXIT_FAILURE);
	if (option->pre > 0)
	{
		box[0] = '.';
		i = 0;
		while (i < option->pre)
		{
			fpart = fpart * 10;
			box[i + 1] = 48 + ((((int)fpart) % 10));
			fpart = fpart - (int)fpart;
			i++;
		}
		box[i + 1] = '\0';
	}
	return (box);
}

static int	format_dbl(t_parameter *li, long double number)
{
	unsigned long long	ipart;
	long double			fpart;
	char				*temp;
	char				*test;
	int					size;

	size = 0;
	test = NULL;
	if (number != number)
		number = 0.000000;
	number = set_dbl_negtif(number, li);
	ipart = (unsigned long long)number;
	fpart = number - (long double)ipart;
	temp = ft_uitoa_base(ipart, 10);
	test = set_fpart(test, li, fpart);
	temp = ft_strjoin_replace(temp, test, 0);
	ft_memdel((void *) &test);
	if ((number >= 1) || (number < 1 && li->pre > 1))
		temp = rounding(temp, getdigit(li->pre, fpart), \
		(ft_strlen(temp) - 1), li);
	else
		temp = round2(temp, getdigit(li->pre, fpart), number, li);
	size = print_int(li, temp);
	ft_memdel((void *) &temp);
	return (size);
}

/*turn va_arg into a double or long double*/
int	conv_to_dbl(t_parameter *li, va_list ap)
{
	long double	number;

	if (!li->dot)
		li->pre = 6;
	if (!ft_strcmp(li->sizeprefix, "L"))
		number = va_arg(ap, long double);
	else if (!ft_strcmp(li->sizeprefix, "l"))
		number = va_arg(ap, double);
	else
		number = va_arg(ap, double);
	if (ft_isinf(number))
		return (format_str("inf", li));
	return (format_dbl(li, number));
}
