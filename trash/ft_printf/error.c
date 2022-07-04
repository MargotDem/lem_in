/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:53:13 by briffard          #+#    #+#             */
/*   Updated: 2022/05/06 09:03:34 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				error(const char *message);
t_parameter		*checkoptionerror(t_parameter *options);

t_parameter	*checkoptionerror(t_parameter *options)
{
	if (options->flags & F_ZERO && options->flags & F_MINUS)
		options->flags = options->flags ^ F_ZERO;
	if (options->flags & F_SPACE && options->flags & F_PLUS)
		options->flags = options->flags ^ F_SPACE;
	if (options->flags & F_SPACE && \
		(options->conv != 'd' && options->conv != 'i' && \
		options->conv != 'f'))
		options->flags = options->flags ^ F_SPACE;
	if (options->flags & F_PLUS && \
	(options->conv == 'u' || options->conv == 'x' || options->conv == 'p' || \
	options->conv == 'o'))
		options->flags = options->flags ^ F_PLUS;
	if (options->dot && options->conv == 'o' && options->flags & F_ZERO)
		options->flags = options->flags ^ F_ZERO;
	return (options);
}

int	error(const char *message)
{
	write(2, message, ft_strlen(message));
	return (-1);
}
