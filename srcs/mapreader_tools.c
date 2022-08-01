/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapreader_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:31:05 by briffard          #+#    #+#             */
/*   Updated: 2022/08/01 12:32:27 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*add_buffer_to(char **str, char *buffer)
{
	char	*temp;

	if (!(*str))
	{
		*str = (char *)malloc(sizeof(char) * BUFF_SIZE + 1);
		if (!(*str))
			return (NULL);
		ft_bzero(*str, BUFF_SIZE);
	}
	temp = ft_strjoin(*str, buffer);
	if (!temp)
		return (NULL);
	ft_memdel((void **)(&(*str)));
	*str = temp;
	return (*str);
}

char	*readmap(char *map)
{
	int		ret;
	char	buffer[10000];

	ret = read(0, buffer, 10000);
	while (ret > 0)
	{
		buffer[ret] = '\0';
		map = add_buffer_to(&map, buffer);
		ret = read(0, buffer, 10000);
	}
	return (map);
}
