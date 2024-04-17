/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:24:02 by mateo             #+#    #+#             */
/*   Updated: 2024/04/17 15:32:41 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*	ft_parse_line0 parses the first line of fdf file
	- adds height and width into fdf */
void	ft_parse_line0(char *file, t_fdf *fdf)
{
	char	*line;

	line = get_next_line(fdf->map_fd, 0);
	if (!line)
		ft_parse_map_error(fdf, ERR_FILE, -2);
	fdf->split = ft_split(line, ' ', '\n');
	free(line);
	fdf->map_height = ft_map_height(file, fdf);
	fdf->map = malloc(sizeof(t_pt *) * fdf->map_height);
	if (!fdf->map)
		ft_parse_map_error(fdf, ERR_MALLOC_MAP, -2);
	fdf->map_width = ft_count_split(fdf->split);
	if (fdf->map_width == 0 || fdf->map_height == 0)
		ft_parse_map_error(fdf, ERR_FILE, -1);
	fdf->map[0] = ft_fill_pt(fdf, 0);
}

/*	ft_get_z extracts z 
	and checks that it is not beyond INT_MAX and INT_MIN*/
int	ft_get_z(t_fdf *fdf, int x, t_pt *row, int y)
{
	int	z;

	z = ft_atoi(fdf->split[x]);
	if ((z == 0 && fdf->split[x][0] != '0') || \
		(z == -1 && fdf->split[x][0] != '-') || \
		(z > 0 && ft_first_digit(z) != fdf->split[x][0]) || \
		(z < 0 && ft_first_digit(-z) != fdf->split[x][1]))
	{
		free(row);
		ft_parse_map_error(fdf, ERR_LIMITS, y - 1);
	}
	return (z);
}

/* ft_fill_pt parses array of str into array of t_pt 
	- frees split after parsing */
t_pt	*ft_fill_pt(t_fdf *fdf, int y)
{
	int		x;
	t_pt	*row;

	row = malloc(sizeof(t_pt) * fdf->map_width);
	if (!row)
		ft_parse_map_error(fdf, ERR_MALLOC_ROW, y - 1);
	x = 0;
	while (fdf->split[x])
	{
		row[x].x = x;
		row[x].y = y;
		if (ft_strisnum(fdf->split[x]) == 1)
			row[x].z = ft_get_z(fdf, x, row, y);
		else
		{
			free(row);
			ft_parse_map_error(fdf, ERR_FILE, y - 1);
		}
		row[x].colour = ft_map_colour(row, x, fdf);
		x++;
	}
	ft_free_arrstr(fdf);
	return (row);
}

/*	ft_parse_lines parses the rest of fdf file*/
void	ft_parse_lines(t_fdf *fdf)
{
	int		y;
	char	*line;

	y = 1;
	while (y < fdf->map_height)
	{
		line = get_next_line(fdf->map_fd, 0);
		if (!line)
			ft_parse_map_error(fdf, ERR_FILE, y - 1);
		fdf->split = ft_split(line, ' ', '\n');
		free(line);
		if (ft_count_split(fdf->split) == fdf->map_width)
		{
			fdf->map[y] = ft_fill_pt(fdf, y);
			y++;
		}
		else
			ft_parse_map_error(fdf, ERR_FILE, y - 1);
	}
}
