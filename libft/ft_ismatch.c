/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ismatch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 20:51:29 by mde-maul          #+#    #+#             */
/*   Updated: 2021/10/31 20:51:33 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ismatch(const char *haystack, const char *needle, int i)
{
	int	j;

	j = 0;
	if (ft_strlen(needle) > ft_strlen(&haystack[i]))
		return (0);
	while (needle[j])
	{
		if (haystack[i + j] != needle[j])
			return (0);
		j++;
	}
	return (1);
}
