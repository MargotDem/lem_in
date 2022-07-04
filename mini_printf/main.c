#include "mini_printf.h"

int print_all(t_string *li)
{
    char *dest;
    t_string *temp;

    temp = li;
    dest = ft_strnew(1);
    while (temp != NULL)
    {
        dest = ft_strcat(dest, temp->str);
        temp = temp->next;
    }
    ft_putstr(dest);
    int size = ft_strlen(dest);
    free(dest);
    dest = NULL;
    return (size);

}

static int add_str_to_list(const char *format, t_string **li)
{
    char *temp;
    int i;

    i = 0;
    while (format[i] != '%' && format[i] != '\0')
        i++;
    temp = ft_strsub(format, 0, i - 0);
    push_t_string(li, temp);
    free(temp);
    temp = NULL;
    return (i);
}


static void	dispatch(va_list ap, t_string **li, char c)
{
	// if (c == '%')
	// 	return (format_char(li, '%'));
	// else
		g_funcflagsarray[c - 'a'](li, ap);
}


int mini_printf(const char *format, ...)
{
    int index;
    va_list ap;
    t_string    *new;

    index = 0;
    va_start(ap, format);
    while(format[index] != '\0')
    {
        if(format[index] == '%')
        {
            dispatch(ap, &new, format[index + 1]);
			index += 2;
        }
        else
            index += add_str_to_list(&format[index], &new);
    }
    va_end(ap);
    return (print_all(new));
}

int main(void)
{
    printf("PF: Hello\n");
    mini_printf("FT: Hello\n");
    printf("PF: Hello %s\n", "World");
    mini_printf("FT: Hello %s\n", "World");
    return (0);
}