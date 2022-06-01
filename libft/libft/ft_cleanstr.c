/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:46:32 by briffard          #+#    #+#             */
/*   Updated: 2022/01/07 09:28:55 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_cleanstr(char	**s, size_t	i )
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		free (s[j]);
		j++;
	}
	free (s);
	return (NULL);
}
