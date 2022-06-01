/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:02:39 by briffard          #+#    #+#             */
/*   Updated: 2022/01/07 09:43:34 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequ(char const *s1, char const	*s2)
{
	if (!s1 || !s2)
		return (0);
	if (ft_strcmp(s1, s2) == 0)
		return (1);
	else
		return (0);
}
