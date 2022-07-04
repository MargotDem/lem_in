/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:27:52 by briffard          #+#    #+#             */
/*   Updated: 2022/05/06 09:05:25 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_parameter			*init(const char *format, t_parameter *option, va_list ap);
int					checkparams(char c);
static void			resetoption(t_parameter *li, char *str);
static t_parameter	*setup(char *str, t_parameter *li, va_list ap);

/*RESET ALL PARAMETERS*/
static void	resetoption(t_parameter *option, char *str)
{
	option->upper = 0;
	if (ft_isupper(str[ft_strlen(str) - 1]))
		option->upper = 1;
	option->width = 0;
	option->dot = 0;
	option->error = 0;
	option->pre = 0;
	option->char_to_skip = 0;
	ft_bzero(option->sizeprefix, 5);
	option->size = ft_strlen(str);
	option->negatif = 0;
	option->length = 0;
	option->conv = ft_tolower(str[ft_strlen(str) - 1]);
	option->adddot = 0;
}

/*PARSE PARAMETERS STR TO DEFINE THEM INTO THE STRUCT*/
static t_parameter	*setup(char *str, t_parameter *li, va_list ap)
{
	resetoption(li, str);
	handle_flag(str, li);
	handle_width(&str[li->char_to_skip], li, ap);
	handle_precision(&str[li->char_to_skip], li, ap);
	handle_size_prefix(&str[li->char_to_skip], li);
	checkoptionerror(li);
	return (li);
}

/*LOOKING FOR THE FLAG*/
int	checkparams(char c)
{
	size_t	i;

	i = 0;
	while (ARRFLAGS[i] != '\0')
	{
		if (c == ARRFLAGS[i])
			return (0);
		i++;
	}
	return (1);
}

t_parameter	*init(const char *format, t_parameter *option, va_list ap)
{
	char		*temp;
	char		*parameters;
	int			index;

	index = 1;
	while (checkparams(format[index]) && format[index] != '\0')
		index++;
	if (index == (int)ft_strlen(format))
		return (NULL);
	temp = ft_strsub(format, 1, index);
	parameters = temp;
	ft_memdel((void *)&temp);
	if (!parameters)
		exit(EXIT_FAILURE);
	if (!option)
	{
		option = (t_parameter *)malloc(sizeof(*option));
		if (!option)
			exit(EXIT_FAILURE);
	}
	setup(parameters, option, ap);
	return (option);
}
