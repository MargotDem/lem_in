/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:16:30 by mde-maul          #+#    #+#             */
/*   Updated: 2021/12/28 18:16:34 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	handle_line(char **fd_array, int fd, char **line)
{
	char	*tmp;
	int		length;

	length = 0;
	while (fd_array[fd][length] != '\0' && fd_array[fd][length] != '\n')
		length++;
	if (fd_array[fd][length] == '\n')
	{
		*line = ft_strsub(fd_array[fd], 0, length);
		tmp = ft_strdup(&fd_array[fd][length + 1]);
		ft_memdel((void **)&fd_array[fd]);
		fd_array[fd] = tmp;
		if (*fd_array[fd] == '\0')
			ft_memdel((void **)&fd_array[fd]);
	}
	else
	{
		*line = ft_strdup(fd_array[fd]);
		ft_memdel((void **)&fd_array[fd]);
	}
}

static int	handle_ret(char **fd_array, int fd, char **line, int ret)
{
	if (ret == 0 && !fd_array[fd])
		return (0);
	if (ret < 0)
		return (-1);
	handle_line(fd_array, fd, line);
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	static char	*fd_array[FD_ARRAY_SIZE];
	char		buf[BUFF_SIZE + 1];
	int			ret;
	char		*tmp;

	if (fd < 0 || fd >= FD_ARRAY_SIZE || !line || BUFF_SIZE < 1)
		return (-1);
	ret = read(fd, buf, BUFF_SIZE);
	buf[ret] = '\0';
	while (ret > 0)
	{
		if (!fd_array[fd])
			fd_array[fd] = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(fd_array[fd], buf);
			ft_memdel((void **)&fd_array[fd]);
			fd_array[fd] = tmp;
		}
		if (ft_strchr(buf, '\n'))
			break ;
		ret = read(fd, buf, BUFF_SIZE);
		buf[ret] = '\0';
	}
	return (handle_ret(fd_array, fd, line, ret));
}
