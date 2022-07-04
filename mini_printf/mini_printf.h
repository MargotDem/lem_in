#ifndef MINI_PRINTF_H
# define MINI_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>


typedef struct s_string {
    char *str;
    struct s_string *next;
}   t_string;



/*DISPATCH TABLE*/
/*FUNCTION IN DISPATCH FLAG ARRAY*/
void	conv_to_str(t_string **li, va_list ap);

typedef void						(*t_dispatchflags)(t_string **li, va_list ap);
static const t_dispatchflags	g_funcflagsarray[26] = {
	NULL,
	NULL,
    NULL,
    NULL,
	NULL,
    NULL,
	NULL,
	NULL,
    NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
    NULL,
	NULL,
	NULL,
	conv_to_str,
    NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
};

int 	mini_printf(const char *formart, ...);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char	*s);
char	*ft_strnew(size_t size);
char	*ft_strsub(char const	*s, unsigned int start, size_t len);
void    push_t_string(t_string **li, const char *str);
t_string *new_node(const char *str);
char	*ft_strjoin(char const	*s1, char const	*s2);
void	ft_putstr(char *str);
char	*ft_strcat(char	*s1, char const *s2);

#endif

