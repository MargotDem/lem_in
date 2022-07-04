#include "mini_printf.h"


t_string *new_node(const char *str)
{
    t_string *node;

    node = (t_string *)malloc(sizeof(*node));
    if (!node)
        exit(EXIT_FAILURE);
    node->str = ft_strdup(str);
    node->next =  NULL;
    return (node);
}

t_string *push_back(t_string *li, t_string *element)
{
    t_string *temp;
    
    if (!li)
        return (element);
    temp = li;
    while(temp->next != NULL)
        temp = temp->next;
    temp->next = element;
    element->next = NULL;
    return (li);    
}

void    push_t_string(t_string **li, const char *str)
{
    t_string    *element;

    element = new_node(str);
    *li = push_back(*li, element);
}


int	format_str(const char *str, t_string **li)
{
	int	size;

	size = 0;
	if (str == NULL)
		str = "(null)";
	// if (is_bonus(str))
	// {
	// 	ft_putstr(str);
	// 	return (0);
	// }
    push_t_string(li, str);


	return (size);
}


void	conv_to_str(t_string **li, va_list ap)
{
    format_str(va_arg(ap, char *), li);
}