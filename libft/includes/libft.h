/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:08:45 by briffard          #+#    #+#             */
/*   Updated: 2022/10/05 12:33:52 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include<unistd.h>
# include<stdlib.h>
# include<string.h>
# include<fcntl.h>
# include<time.h>
# include "ft_printf.h"

/*DEFINE*/
/*COLOR*/
# define DEFAULT	"\x1B[0m"
# define RED		"\x1B[31m"
# define GREEN	"\x1B[32m"
# define YELLOW	"\x1B[33m"
# define BLUE	"\x1B[34m"
# define MAGENTA	"\x1B[35m"
# define CYAN	"\x1B[36m"
# define WHITE	"\x1B[37m"
/*FT_PRINTF*/
# define RESETALL	"\033[0m"
# define BOLD	"\033[1m"
# define UNDERLINED	"\033[4m"
# define BLINK	"\033[5m"
# define RESETBOLD	"\033[21m"
# define RESETUNDERLINED	"\033[24m"
# define RESETBLINK	"\033[25m"
/*DEFINE GNL*/
# define BUFF_SIZE 10000
# define FD_ARRAY_SIZE 4096

/*DEFINE ITOA_BASE*/
# define BASE "0123456789abcdef"

typedef struct s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

/*FT_STR FUNCTION*/
/*RETURN INT*/
int					ft_strcmp(const char *s1, const char	*s2);
int					ft_strncmp(const char *s1, const char	*s2, size_t	n);
int					ft_strequ(char const *s1, char const	*s2);
int					ft_strnequ(char const *s1, char const	*s2, size_t	n);
size_t				ft_strlcat(char	*dst, const char *src, size_t stsize);
size_t				ft_strlen(char const *s);
/*RETURN VOID*/
void				ft_strclr(char	*s);
void				ft_strdel(char	**as);
void				ft_striter(char *s, void (*f)(char *s));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
/*RETURN *CHAR*/
char				*ft_strcat(char	*s1, char const	*s2);
char				*ft_strchr(const char	*s, int c);
char				*ft_strcpy(char	*dst, const char	*src);
char				*ft_strdup(const char	*s1);
char				*ft_strncat(char *s1, char	*s2, size_t	n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strnstr(const char *haystack, \
const char *needle, size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const	char *haystack, const char	*needle);
char				*ft_strtrim(char const	*s);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strmap(char const	*s, char (*f)(char));
char				*ft_strmapi(char const	*s, char (*f)(unsigned int, char));
char				*ft_strnew(size_t size);
char				*ft_strjoin(char const	*s1, char const	*s2);
char				*ft_strjoin_replace(char *s1, char *s2, int choice);
char				*ft_charjoin(char c, char *dest);
char				**ft_strsplit(char const *s, char c);
char				*ft_reverse_str(char *str);

/*FT_ TO FUNCION*/
int					ft_tolower(int c);
int					ft_toupper(int c);
char				*ft_strtoupper(char *str);
int					ft_atoi(const char *str);
char				*ft_itoa(int n);
char				*ft_u_itoa(unsigned long long int n);
char				*ft_ll_itoa(long long int number);
char				*ft_l_itoa(long number);
char				*ft_uitoa_base(unsigned long long number, int base);

/*FT_IS FUNCTION*/
int					ft_isupper(int c);
int					ft_isalnum(int c);
int					ft_isdigit(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isalpha(int c);
int					ft_isspace(char c);
int					ft_isdoubleneg(long double x);
int					ft_isintneg(long long int number);

/*FT_PUT FUNCTION*/
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl(char const	*s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr(char const	*s);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putstrcolor(char *str, char *color);
void				ft_putcharcolor(char c, char *color);
int					ft_printbits(void *ptr, int size);
void				ft_display_file(int fd);

/*MEM FUNCTION*/
void				*ft_memalloc(size_t	size);
void				*ft_memchr(const void *s, int c, size_t n);
void				ft_memdel(void	**ap);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memcpy(void	*dest, const void	*src, size_t	n);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void	*s, size_t	n);
int					ft_memcmp(const void	*s1, const void	*s2, size_t	n);
void				*ft_cleanstr(char **s, size_t i);

/*BONUS FUNCTIONS*/
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));

/*EXTRA FUNCTION*/

void				ft_color(const char *s);
int					ft_randomnbr(void);
int					get_next_line(const int fd, char **line);
void				ft_swap(char *a, char *b);

/*MATH*/
double				ft_abs_float(double value);
long long			ft_abs_int(long long value);
unsigned long long	ft_numlength(unsigned long long int n);
#endif
