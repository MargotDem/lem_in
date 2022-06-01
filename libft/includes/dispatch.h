/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 10:12:21 by briffard          #+#    #+#             */
/*   Updated: 2022/05/06 09:01:25 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPATCH_H
# define DISPATCH_H

typedef unsigned char			t_uchar;
typedef struct s_parameter
{
	t_uchar		flags;
	int			width;
	char		conv;
	int			upper;
	int			negatif;
	int			dot;
	int			error;
	int			length;
	int			pre;
	int			char_to_skip;
	char		sizeprefix[5];
	int			size;
	int			adddot;
}				t_parameter;

/*DISPATCH TABLE*/
/*FUNCTION IN DISPATCH FLAG ARRAY*/
int	conv_to_str(t_parameter *li, va_list ap);
int	conv_to_int(t_parameter *li, va_list ap);
int	conv_to_uint(t_parameter *li, va_list ap);
int	conv_to_ptr(t_parameter *li, va_list ap);
int	conv_to_dbl(t_parameter *li, va_list ap);
int	conv_to_void(t_parameter *li, va_list ap);

typedef int						(*t_dispatchflags)(t_parameter *li, va_list ap);
static const t_dispatchflags	g_funcflagsarray[26] = {
	NULL,
	conv_to_void,
	conv_to_int,
	conv_to_int,
	NULL,
	conv_to_dbl,
	NULL,
	NULL,
	conv_to_int,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	conv_to_uint,
	conv_to_ptr,
	NULL,
	NULL,
	conv_to_str,
	conv_to_int,
	conv_to_uint,
	NULL,
	NULL,
	conv_to_uint,
	NULL,
	NULL,
};

#endif
