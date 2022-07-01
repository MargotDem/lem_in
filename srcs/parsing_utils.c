#include "parsing.h"

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

/*Extract room name in line*/
char	*extract_name(char *line)
{
	int	i;
	int start;
	char *name;

	i = 0;
	while (ft_iswhitespace(line[i]))
		i++;
	start = i;
	while (line[i] > 32)
		i++;
	name = ft_strsub(line, start, i - start);
	if(!name)
		err_handling("malloc");
	return (name);
}

/*Extract an int line from line*/
int	extract_line(char *line)
{
	int	i;

	i = 0;
	i += skip_space(line);
	i += skip_word(&line[i]);
	return (ft_atoi(&line[i]));
}

/*Extrac an int row from line*/
int	extract_row(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (ft_isdigit(line[i]))
		i--;
	return (ft_atoi(&line[i]));
}

int	check_word(char **arr)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (arr[i][x] != '\0')
    {
        x = 0;
        while (arr[i][x] != '\0')
        {
            if (i == 0)
            {
				if (!ft_isprint(arr[i][x]))
                    return (1);
			}
            else
            {
				if (!ft_isdigit(arr[i][x]))
                    return (1);
			}
            x++;
        }
    i++;
    }
	return (0);
}