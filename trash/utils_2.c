#include "lem_in.h"

/*count how many word in line*/
int	countwords(char const *s, char c)
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

/*Verifie une chaine de caractere pour savoir il y autre qu un digit*/
int check_digit(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0' && !ft_iswhitespace(str[i]))
    {
        if(!ft_isdigit(str[i]))
            return (-1);
        i++;
    }
    return (i);
}

/*Verifie une chaine de caractere pour trouver autre caratere que print*/
int check_name(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0' && !ft_iswhitespace(str[i]))
    {
        if(!ft_isprint(str[i]))
            return (-1);
        i++;
    }
    return (i);
}
