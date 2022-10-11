/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 20:08:55 by mde-maul          #+#    #+#             */
/*   Updated: 2022/10/11 20:08:57 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	get_answer(float ans, int number)
{
	float	increment;
	int		i;

	increment = 0.1;
	i = 0;
	while (i < 5)
	{
		while (ans * ans <= number)
			ans += increment;
		ans = ans - increment;
		increment = increment / 10;
		i++;
	}
	return (ans);
}

float	ft_sqrt(int number)
{
	int		start;
	int		end;
	int		mid;
	float	ans;

	start = 0;
	end = number;
	while (start <= end)
	{
		mid = (start + end) / 2;
		if (mid * mid == number)
		{
			ans = mid;
			break ;
		}
		if (mid * mid < number)
		{
			ans = start;
			start = mid + 1;
		}
		else
			end = mid - 1;
	}
	return (get_answer(ans, number));
}
