/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:00:06 by briffard          #+#    #+#             */
/*   Updated: 2022/04/25 09:44:36 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char	*s1, char const *s2)
{
	size_t	len_s1;

	len_s1 = ft_strlen(s1);
	ft_memcpy(s1 + len_s1, s2, ft_strlen(s2));
	ft_bzero(s1 + len_s1 + ft_strlen(s2), 1);
	return (s1);
}
