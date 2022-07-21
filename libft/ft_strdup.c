/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:35:16 by mde-maul          #+#    #+#             */
/*   Updated: 2021/10/29 17:35:18 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char		*cpy;
	size_t		len;

	len = ft_strlen(s1);
	cpy = ft_strnew(len);
	if (!cpy)
		return (NULL);
	ft_strcpy(cpy, s1);
	return (cpy);
}
