/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:07:52 by briffard          #+#    #+#             */
/*   Updated: 2022/01/07 09:48:51 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const	*s)
{
	size_t	start;
	size_t	end;
	char	*cpy;
	size_t	i;

	i = 0;
	start = 0 ;
	if (!s)
		return (NULL);
	end = ft_strlen(s) - 1;
	while (ft_isspace(s[start]))
		start++;
	if (start == ft_strlen(s))
		return ("\0");
	while (ft_isspace(s[end]))
		end--;
	end += 1;
	cpy = (char *)malloc(sizeof(char) * (end - start) + 1);
	if (!cpy)
		return (NULL);
	while (start < end)
		cpy[i++] = s[start++];
	cpy[i] = '\0';
	return (cpy);
}
