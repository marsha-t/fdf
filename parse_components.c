/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_components.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:11:02 by mateo             #+#    #+#             */
/*   Updated: 2024/04/17 15:08:49 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*	ft_map_height_count reads from reopened file and 
	counts number of newlines */
int	ft_map_height_count(t_fdf *fdf)
{
	int		height;
	char	*buffer;
	int		r;

	height = 0;
	buffer = malloc(sizeof(char) * 5);
	if (!buffer)
		ft_parse_map_error(fdf, ERR_MALLOC_BUF, -2);
	buffer[4] = '\0';
	r = 1;
	while (r > 0)
	{
		r = read(fdf->map_height_fd, buffer, 4);
		height += ft_nl_read(buffer);
		ft_bzero(buffer, 5);
	}
	free(buffer);
	if (r < -1)
		ft_parse_map_error(fdf, ERR_READ, -2);
	return (height);
}

/* ft_map_height returns the height of the map */
int	ft_map_height(char *file, t_fdf *fdf)
{
	int		height;

	fdf->map_height_fd = open(file, O_RDONLY);
	if (fdf->map_height_fd == -1)
		ft_parse_map_error(fdf, ERR_OPEN, -2);
	height = ft_map_height_count(fdf);
	if (close(fdf->map_height_fd) == -1)
	{
		fdf->map_height_fd = -1;
		ft_parse_map_error(fdf, ERR_CLOSE, -2);
	}
	fdf->map_height_fd = -1;
	return (height);
}

/* ft_map_colour parses the colour given in the map into a DECIMAL number
	- checks that the colour is provided correctly
	- parses a correctly provided colour and returns the DECIMAL number
	- returns a default colour if none is provided*/
int	ft_map_colour(t_pt *row, int x, t_fdf *fdf)
{
	char	*str;

	str = fdf->split[x];
	while (*str && *str != ',')
		str++;
	if (*str == ',' && ft_check_colour(str + 1) == 1)
	{
		str += 3;
		str = ft_struppr(str);
		return (ft_atoi_base(str, "0123456789ABCDEF"));
	}
	else if (*str == ',' && ft_check_colour(str + 1) == 0)
	{
		close(fdf->map_fd);
		ft_free_arrstr(fdf);
		ft_free_fdf(fdf, row->y - 1);
		free(row);
		ft_error(ERR_FILE);
	}
	return (DEFAULT_COLOUR);
}
