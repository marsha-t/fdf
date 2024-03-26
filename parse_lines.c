/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:24:02 by mateo             #+#    #+#             */
/*   Updated: 2024/03/26 16:25:14 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*	ft_parse_line0 parses the first line of fdf file
	- adds height and width into fdf */
void	ft_parse_line0(char *file, t_fdf *fdf)
{
	char	*line;
	char	**split;

	line = get_next_line(fdf->map_fd, 0);
	if (!line)
		ft_parse_map_error(fdf, 0, ERR_FILE, -2);
	split = ft_split(line, ' ');
	free(line);
	fdf->map_height = ft_map_height(file, split, fdf);
	fdf->map = malloc(sizeof(t_pt *) * fdf->map_height);
	if (!fdf->map)
		ft_parse_map_error(fdf, split, ERR_MALLOC_MAP, -2);
	fdf->map_width = ft_count_split(split);
	fdf->map[0] = ft_fill_pt(fdf, split, 0);
}

/* ft_map_height returns the height of the map */
int	ft_map_height(char *file, char **split, t_fdf *fdf)
{
	int		height;
	char	*buffer;
	int		r;

	fdf->map_height_fd = open(file, O_RDONLY);
	if (fdf->map_height_fd == -1)
		ft_parse_map_error(fdf, split, ERR_OPEN, -2);
	height = 0;
	buffer = malloc(sizeof(char) * 5);
	if (!buffer)
		ft_parse_map_error(fdf, split, ERR_MALLOC_BUF, -2);
	buffer[4] = '\0';
	r = 1;
	while (read(fdf->map_height_fd, buffer, 4) > 0)
		height += ft_nl_read(buffer);
	free(buffer);
	if (read(fdf->map_height_fd, buffer, 4) < -1)
		ft_parse_map_error(fdf, split, ERR_READ, -2);
	if (close(fdf->map_height_fd) == -1)
	{
		fdf->map_height_fd = -1;
		ft_parse_map_error(fdf, split, ERR_CLOSE, -2);
	}
	fdf->map_height_fd = -1;
	return (height);
}

/* ft_fill_pt parses array of str into array of t_pt 
	- frees split after parsing */
t_pt	*ft_fill_pt(t_fdf *fdf, char **split, int y)
{
	int		x;
	t_pt	*row;

	row = malloc(sizeof(t_pt) * fdf->map_width);
	if (!row)
		ft_parse_map_error(fdf, split, ERR_MALLOC_ROW, y - 1);
	x = 0;
	while (split[x])
	{
		row[x].x = x;
		row[x].y = y;
		if (ft_strisnum(split[x]) == 1)
			row[x].z = ft_atoi(split[x]);
		else
		{
			free(row);
			ft_parse_map_error(fdf, split, ERR_FILE, y - 1);
		}
		row[x].colour = ft_map_colour(split, row, x, fdf);
		x++;
	}
	ft_free_arrstr(split);
	return (row);
}

/* ft_map_colour parses the colour given in the map into a DECIMAL number
	- checks that the colour is provided correctly
	- parses a correctly provided colour and returns the DECIMAL number
	- returns a default colour if none is provided*/
int	ft_map_colour(char **split, t_pt *row, int x, t_fdf *fdf)
{
	char	*str;

	str = split[x];
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
		ft_free_arrstr(split);
		ft_free_fdf(fdf, row->y - 1);
		free(row);
		ft_error(ERR_FILE);
	}
	return (DEFAULT_COLOUR);
}

/*	ft_parse_lines parses the rest of fdf file*/
void	ft_parse_lines(t_fdf *fdf)
{
	int		y;
	char	*line;
	char	**split;

	y = 1;
	while (y < fdf->map_height)
	{
		line = get_next_line(fdf->map_fd, 0);
		if (!line)
			ft_parse_map_error(fdf, 0, ERR_FILE, y - 1);
		split = ft_split(line, ' ');
		free(line);
		if (ft_count_split(split) == fdf->map_width)
		{
			fdf->map[y] = ft_fill_pt(fdf, split, y);
			y++;
		}
		else
			ft_parse_map_error(fdf, split, ERR_FILE, y - 1);
	}
}
