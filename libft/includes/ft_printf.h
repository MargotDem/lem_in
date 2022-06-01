/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:05:56 by briffard          #+#    #+#             */
/*   Updated: 2022/05/30 15:22:00 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*INCLUDE*/
# include <stdarg.h>
# include <unistd.h>
# include "libft.h"
# include "dispatch.h"

/*DEFINE*/
# define F_HASHTAG 0x80
# define F_ZERO 0x40
# define F_PLUS 0x20
# define F_MINUS 0x10
# define F_SPACE 0x08
# define F_NEGATIF 0x04
# define F_MOD 0x02

# define ARRFLAGS "scdxXop%ifutb"

/*PROTOTYPE*/
int			ft_printf(const char *format, ...);

/*FUNCTIONS*/
/*STRUCT_INIT.C*/
t_parameter	*init(const char *format, t_parameter *li, va_list ap);
int			checkparams(char c);

/*HANDLE_FLAG*/
t_parameter	*handle_flag(char *str, t_parameter *li);
t_parameter	*handle_width(char *str, t_parameter *li, va_list ap);
t_parameter	*handle_precision(char *str, t_parameter *li, va_list ap);
t_parameter	*handle_size_prefix(char *str, t_parameter *li);

/*ERROR.C*/
t_parameter	*checkoptionerror(t_parameter *option);
int			error(const char *message);

/*CONV_INT.C*/
int			format_char(t_parameter *option, char c);
int			set_negatif(int number, t_parameter *option);

/*CONV_STR.C*/
int			format_str(const char *str, t_parameter *option);

/*CONV_UINT.C*/
int			format_uint(t_parameter *option, unsigned int number);
int			u_ll_itoa(t_parameter *option, unsigned long long int number);

/*PRINT_INT.C*/
int			print_int(t_parameter *option, char *str);
void		set_length(t_parameter *option, char *str);
int			print_precision(int start, t_parameter *option, char *str);
int			print_sign(t_parameter *option);
int			print_0x(t_parameter *option, char *str);

/*PRINT_STR.C*/
int			print_width(t_parameter *option, int length);
int			print_str(const char *str, int length, t_parameter *option);
int			print_char(char c);
int			align_right(int start, int length);

/*handle_sizePrefix_for_flag_d.c*/
int			dispatch_to_intsizeprefix(t_parameter *option, va_list ap);
int			ll_int_to_arr(t_parameter *option, long long number);
int			short_int_to_arr(t_parameter *option, short int number);
int			char_to_arr(t_parameter *option, char number);

/*UTILS_FUNCT.C*/
int			define_base(t_parameter *option);
int			skip(char *str);
int			isnot_sizeprefix(char *str);
int			isnot_precision(int c);
long double	set_dbl_negtif(long double number, t_parameter *option);

/*UTILS_PRINT_INT.C*/
int			add_character_f_hashtag(t_parameter *option);
int			set_space(t_parameter *option, char *str);
int			set_zero(t_parameter *option, char *str);
void		adjust_length(t_parameter *option, char *str, int to_remove);
int			align(char *str, t_parameter *option);

/*UTILS_PRINT_INT2.C*/
int			print_sign(t_parameter *option);
int			print_0x(t_parameter *option, char *str);

/*FT_STR_ROUDING*/
char		*rounding(char *number, int fpart, int last_index, \
t_parameter *option);
char		*formatrounding(char *number, int last_index);
char		*round2(char *str, int fpart, long double number, t_parameter *li);

/*BONUS.C*/
int			is_bonus(const char *s);

#endif
