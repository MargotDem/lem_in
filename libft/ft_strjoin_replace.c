/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_replace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:44:10 by mde-maul          #+#    #+#             */
/*   Updated: 2022/03/23 19:44:12 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_replace(char *s1, char *s2, int first_str)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	if (first_str)
		free(s1);
	else
		free(s2);
	return (tmp);
}
