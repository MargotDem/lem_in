/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 11:04:06 by briffard          #+#    #+#             */
/*   Updated: 2022/05/13 08:09:49 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			is_bonus(const char *s);
static int	is_color(const char *s);
static int	is_bold(const char *s);
static int	is_blink(const char *s);
static int	is_underline(const char *s);

static int	is_underline(const char *s)
{
	if (!ft_strcmp(s, UNDERLINED) || !ft_strcmp(s, RESETUNDERLINED))
		return (1);
	return (0);
}

static int	is_bold(const char *s)
{
	if (!ft_strcmp(s, BOLD) || !ft_strcmp(s, RESETBOLD))
		return (1);
	return (0);
}

static int	is_blink(const char *s)
{
	if (!ft_strcmp(s, BLINK) || !ft_strcmp(s, RESETBLINK))
		return (1);
	return (0);
}

/*
** Receive s and check if s == a color
** Return 1 or 0
*/
static int	is_color(const char *s)
{
	if (!ft_strcmp(s, RED))
		return (1);
	if (!ft_strcmp(s, DEFAULT))
		return (1);
	if (!ft_strcmp(s, GREEN))
		return (1);
	if (!ft_strcmp(s, YELLOW))
		return (1);
	if (!ft_strcmp(s, BLUE))
		return (1);
	if (!ft_strcmp(s, MAGENTA))
		return (1);
	if (!ft_strcmp(s, CYAN))
		return (1);
	if (!ft_strcmp(s, WHITE))
		return (1);
	return (0);
}

/*
**Check if s == bonus
*/
int	is_bonus(const char *s)
{
	if (is_color(s))
		return (1);
	if (is_underline(s))
		return (1);
	if (is_bold(s))
		return (1);
	if (is_blink(s))
		return (1);
	return (0);
}
