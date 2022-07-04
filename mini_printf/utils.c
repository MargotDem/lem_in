#include "mini_printf.h"

void	ft_bzero(void	*s, size_t	n);
void	*ft_memalloc(size_t	size);
char	*ft_strcpy(char	*dst, const char	*src);
char	*ft_strncpy(char	*dst, const char	*src, size_t	len);
void	*ft_memcpy(void	*dest, const void	*src, size_t n);
char	*ft_strcat(char	*s1, char const *s2);

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		i;

	i = 0;
	dup = ft_strnew(ft_strlen(s1));
	if (!dup)
		return (NULL);
	while (s1[i] != '\0')
	{
		dup[i] = s1[i];
		i++;
	}
	return (dup);
}

char	*ft_strnew(size_t size)
{
	return ((char *)ft_memalloc(size + 1));
}

void	*ft_memalloc(size_t	size)
{
	unsigned char	*arr;

	arr = (unsigned char *)malloc(size);
	if (arr == NULL)
		return (NULL);
	ft_bzero(arr, size);
	return (arr);
}

void	ft_bzero(void	*s, size_t	n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n > 0)
	{
		*p++ = '\0';
		n--;
	}
}

size_t	ft_strlen(const char	*s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strsub(char const	*s, unsigned int start, size_t len)
{
	char	*substr;

	substr = ft_strnew(len);
	if (!substr)
		return (NULL);
	ft_strncpy(substr, s + start, len);
	return (substr);
}

char	*ft_strncpy(char	*dst, const char	*src, size_t	len)
{
	if (ft_strlen(src) < len)
	{
		ft_strcpy(dst, src);
		ft_bzero(dst + ft_strlen(src), len - ft_strlen(src));
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}

char	*ft_strcpy(char	*dst, const char	*src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void	*ft_memcpy(void	*dest, const void	*src, size_t n)
{
	unsigned char	*pdst;

	if (n && (!dest && !src))
		return (NULL);
	pdst = (unsigned char *)dest;
	while (n--)
		*pdst++ = *(unsigned char *)src++;
	return (dest);
}

char	*ft_strjoin(char const	*s1, char const	*s2)
{
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	join = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (!join)
		return (NULL);
	ft_strcpy(join, s1);
	ft_strcat(join, s2);
	return (join);
}

char	*ft_strcat(char	*s1, char const *s2)
{
	size_t	len_s1;

	len_s1 = ft_strlen(s1);
	ft_memcpy(s1 + len_s1, s2, ft_strlen(s2));
	ft_bzero(s1 + len_s1 + ft_strlen(s2), 1);
	return (s1);
}

void	ft_putstr(char *str)
{
	write (1, str, ft_strlen(str));
}