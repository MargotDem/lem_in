/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:53:55 by mde-maul          #+#    #+#             */
/*   Updated: 2022/06/01 15:53:57 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	handle_error(void)
{
	write(2, "error\n", 6);
	exit(1);
}

void	*handle_null(void *param)
{
	if (!param)
		handle_error();
	return (param);
}
