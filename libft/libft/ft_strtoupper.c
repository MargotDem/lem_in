/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoupper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 08:46:46 by briffard          #+#    #+#             */
/*   Updated: 2022/04/04 08:47:06 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtoupper(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	return (str);
}
