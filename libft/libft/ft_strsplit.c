/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:06:57 by briffard          #+#    #+#             */
/*   Updated: 2022/01/07 09:47:59 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	countwords(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] != c && s[i])
				i++;
			count++;
		}
	}
	return (count);
}

static	int	countletters(char const *s, int i, char c)
{
	int	count;

	count = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		count++;
	}
	return (count);
}

static	char	**cpyarr(char **dest, char const *s, char c)
{
	int	i;
	int	j;
	int	z;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
		{
			dest[j] = (char *)malloc(sizeof(char) * countletters(s, i, c) + 1);
			if (!dest[j])
				return (ft_cleanstr(dest, j));
			z = 0;
			while (s[i] != c && s[i] != '\0')
				dest[j][z++] = s[i++];
			dest[j][z] = '\0';
			j++;
		}
	}
	dest[j] = 0;
	return (dest);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**dest;

	if (!s)
		return (NULL);
	dest = (char **)malloc(sizeof(char *) * (countwords(s, c)) + 1);
	if (!dest)
		return (NULL);
	if (countwords(s, c) == 0)
	{
		dest[0] = 0;
		return (dest);
	}
	return (cpyarr(dest, s, c));
}
