/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:00:30 by mde-maul          #+#    #+#             */
/*   Updated: 2021/11/01 17:00:34 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char c))
{
	int		i;
	int		len;
	char	*return_str;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	return_str = ft_strnew(len);
	if (!return_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		return_str[i] = f(s[i]);
		i++;
	}
	return_str[i] = '\0';
	return (return_str);
}
