/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:13:10 by mde-maul          #+#    #+#             */
/*   Updated: 2022/07/06 08:42:28 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_substr_nb(char const *s, char c)
{
	int	i;
	int	word_count;
	int	is_word;

	i = 0;
	is_word = 0;
	word_count = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			is_word = 0;
		}
		else
		{
			if (!is_word)
			{
				word_count++;
				is_word = 1;
			}
		}
		i++;
	}
	return (word_count);
}

static int	get_substr_len(char const *s, char c, int index)
{
	int	substr_len;

	substr_len = 0;
	while (s[index + substr_len] != c && s[index + substr_len])
		substr_len++;
	return (substr_len);
}

static int	make_substr(char const *s, char c, char **array, int *int_array)
{
	int		j;
	int		substr_len;
	char	*substr;
	int		index;
	int		substr_nb;

	index = int_array[0];
	substr_nb = int_array[1];
	substr_len = get_substr_len(s, c, index);
	substr = (char *)malloc((substr_len + 1) * sizeof(char));
	if (!substr)
	{
		ft_free_str_array(array, substr_nb - 1);
		return (0);
	}
	j = 0;
	while (j < substr_len)
	{
		substr[j] = s[index + j];
		j++;
	}
	substr[j] = '\0';
	array[substr_nb - 1] = substr;
	index = index + substr_len;
	return (index);
}

static int	fill_array(char const *s, char c, char **array)
{
	int		i;
	int		substr_nb;
	int		int_array[2];

	i = 0;
	substr_nb = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			substr_nb++;
			int_array[0] = i;
			int_array[1] = substr_nb;
			i = make_substr(s, c, array, int_array);
			if (!i)
				return (0);
		}
		else
			i++;
	}
	array[substr_nb] = 0;
	return (1);
}

char	**ft_strsplit(char const *s, char c)
{
	int		substr_nb;
	char	**array;

	if (!s)
		return (NULL);
	substr_nb = get_substr_nb(s, c);
	array = (char **)malloc((substr_nb + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	if (!fill_array(s, c, array))
	{
		free(array);
		return (NULL);
	}
	return (array);
}
