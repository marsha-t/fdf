#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft/libft.h"
#include <math.h>

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_not_base(char *str, char *base)
{
	int	j;

	while (*str)
	{	
		if (ft_strchr(base, *str) == 0)
			return (1);
		str++;
	}
	return (0);
}

int	ft_check_colour(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '0' || str[1] != 'x')
	{
		printf("this\n");
		return (0);
	}
	if (ft_strlen(&str[2]) != 6)
	{
		printf("tat\n");
		return (0);
	}

	if (ft_not_base(&str[2], "0123456789ABCDEF") == 1)
	{
		printf("oi\n");
		return (0);
	}
	return (1);
}
int main(void)
{
	char *str = "0aFFFFFa";
	printf("%d\n", ft_check_colour(str));
}


// static void	iso(int x, int y, int z)
// {
// 	int previous_x;
// 	int previous_y;

// 	previous_x = x;
// 	previous_y = y;
// 	x = (previous_x - previous_y) * cos(0.523599);
// 	y = -z + (previous_x + previous_y) * sin(0.523599);
// 	printf("x, y, z: %d, %d, %d", x, y, z);
// }

// int main(void)
// {
// 	iso(1, 1, 1);
// }