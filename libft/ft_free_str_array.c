/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:54:58 by mde-maul          #+#    #+#             */
/*   Updated: 2021/11/25 13:55:01 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_str_array(char **array, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		ft_strclr(array[i]);
		free(array[i]);
		i++;
	}
}
