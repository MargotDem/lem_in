/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:04:43 by mde-maul          #+#    #+#             */
/*   Updated: 2021/11/01 17:04:46 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int i, char c))
{
	unsigned int		i;
	unsigned int		len;
	char				*return_str;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	return_str = ft_strnew(len);
	if (!return_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		return_str[i] = f(i, s[i]);
		i++;
	}
	return_str[i] = '\0';
	return (return_str);
}
