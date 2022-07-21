/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:18:20 by mde-maul          #+#    #+#             */
/*   Updated: 2022/03/25 13:18:22 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isnan(long double nb)
{
	if (!(nb == 0) && !(nb > 0) && !(nb < 0))
		return (1);
	return (0);
}
