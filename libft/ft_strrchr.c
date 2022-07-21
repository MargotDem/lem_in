/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 13:21:26 by mde-maul          #+#    #+#             */
/*   Updated: 2021/10/31 13:21:29 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		len;
	char	*occurrence;

	i = 0;
	len = ft_strlen(s);
	occurrence = NULL;
	while (i <= len)
	{
		if (s[i] == (char)c)
			occurrence = (char *)&s[i];
		i++;
	}
	return (occurrence);
}
