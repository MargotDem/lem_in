/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:07:38 by briffard          #+#    #+#             */
/*   Updated: 2022/04/13 09:33:11 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const	*s, unsigned int start, size_t len)
{
	char	*substr;

	substr = ft_strnew(len);
	if (!substr)
		return (NULL);
	ft_strncpy(substr, s + start, len);
	return (substr);
}
