/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:13:34 by mateo             #+#    #+#             */
/*   Updated: 2024/04/17 16:23:17 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* ft_nl_read returns the number of new line characters contained in buffer */
int	ft_nl_read(char *buffer)
{
	int	count;

	count = 0;
	while (*buffer)
	{
		if (*buffer == '\n')
			count++;
		buffer++;
	}
	return (count);
}

/* ft_count_split returns the number of strings in an array of strings 
	(assuming that there is a null pointer at the end of the array)*/
int	ft_count_split(char **split)
{
	int	count;

	count = 0;
	while (*split)
	{
		count++;
		split++;
	}
	return (count);
}

/*	ft_strupper converts string to uppercase*/
char	*ft_struppr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
		i++;
	}
	return (str);
}

/*	ft_parse_map_error closes fd(s) and frees resources*/
void	ft_parse_map_error(t_fdf *fdf, char *error, int free_map)
{
	get_next_line(fdf->map_fd, 1);
	if (fdf->map_fd >= 0)
	{
		close(fdf->map_fd);
		fdf->map_fd = -1;
	}
	if (fdf->map_height_fd >= 0)
	{
		close(fdf->map_height_fd);
		fdf->map_height_fd = -1;
	}
	if (fdf->split)
		ft_free_arrstr(fdf);
	ft_free_fdf(fdf, free_map);
	ft_error(error);
}

/*	ft_first_digit returns the first digit of int */
int	ft_first_digit(int x)
{
	int	d;

	d = x;
	while (x / 10 > 0)
	{
		x /= 10;
		d = x;
	}
	return (d);
}
