/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_malloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:38:53 by mde-maul          #+#    #+#             */
/*   Updated: 2022/03/27 18:38:55 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_handle_malloc(void *ptr, void (*handle_error)(void))
{
	if (!ptr)
		handle_error();
	return (ptr);
}
