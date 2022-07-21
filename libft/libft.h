/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:36:20 by mde-maul          #+#    #+#             */
/*   Updated: 2021/10/31 13:09:22 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "string.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list {
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}	t_list;

size_t			ft_strlen(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strdup(const char *s1);
int				ft_atoi(const char *str);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_isascii(int c);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *haystack, const char *needle, \
					size_t len);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putnbr(int n);
char			*ft_itoa(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl(char const *s);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *c));
void			ft_striteri(char *s, void (*f)(unsigned int i, char *c));
char			*ft_strmap(char const *s, char (*f)(char c));
char			*ft_strmapi(char const *s, char (*f)(unsigned int i, char c));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
int				ft_ismatch(const char *haystack, const char *needle, int i);
void			ft_display_list_str(t_list *list);
void			ft_free_str_array(char **array, int len);
void			ft_lstadd_back(t_list *list, t_list *new);
int				ft_iswhitespace(char c);
int				ft_lstsize(t_list *list);
int				ft_abs(int i);
long double		ft_abs_float(long double nb);
int				get_next_line(const int fd, char **line);
int				ft_sqrt(int nb);
char			*ft_itoa_base(int nb, int base);
char			*ft_ull_itoa_base(unsigned long long int nb, int base);
char			*ft_ll_itoa(long long int n);
char			*ft_strjoin_replace(char *s1, char *s2, int first_str);
long long int	ft_abs_ll(long long int i);
long long int	ft_ll_atoi(const char *str);
int				ft_isnan(long double nb);
void			*ft_handle_malloc(void *ptr, void (*handle_error)(void));
char			*ft_strreplace(char *str, char *tmp);

# define BUFF_SIZE 200
# define FD_ARRAY_SIZE 4096

// btrees

typedef struct s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item;
}				t_btree;

t_btree			*btree_create_node(void *item);
void			btree_apply_prefix(t_btree *root, void (*applyf)(void *));
void			btree_apply_infix(t_btree *root, void (*applyf)(void *));
void			btree_apply_suffix(t_btree *root, void (*applyf)(void *));
t_btree			*btree_insert_data(t_btree **root, void *item, \
					int (*cmpf)(void *, void *));
t_btree			*btree_find_node(t_btree *btree, int (*f)(void \
					*cur_node_item, void *looked_for_item), void *item);

#endif
