/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 11:48:22 by briffard          #+#    #+#             */
/*   Updated: 2022/04/15 12:18:57 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_color(const char *s)
{
	if (!ft_strcmp(s, "red") || !ft_strcmp(s, RED))
		ft_putstr(RED);
	if (!ft_strcmp(s, "normal") || !ft_strcmp(s, DEFAULT))
		ft_putstr(DEFAULT);
	if (!ft_strcmp(s, "green") || !ft_strcmp(s, GREEN))
		ft_putstr(GREEN);
	if (!ft_strcmp(s, "yellow") || !ft_strcmp(s, YELLOW))
		ft_putstr(YELLOW);
	if (!ft_strcmp(s, "blue") || !ft_strcmp(s, BLUE))
		ft_putstr(BLUE);
	if (!ft_strcmp(s, "magenta") || !ft_strcmp(s, MAGENTA))
		ft_putstr(MAGENTA);
	if (!ft_strcmp(s, "cyan") || !ft_strcmp(s, CYAN))
		ft_putstr(CYAN);
	if (!ft_strcmp(s, "white") || !ft_strcmp(s, WHITE))
		ft_putstr(WHITE);
}
