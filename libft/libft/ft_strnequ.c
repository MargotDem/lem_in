/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 13:21:59 by briffard          #+#    #+#             */
/*   Updated: 2022/01/07 09:51:13 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const	*s1, char const	*s2, size_t	n)
{
	if (!s1 || !s2)
		return (0);
	if (ft_strncmp(s1, s2, n) == 0)
		return (1);
	else
		return (0);
}
