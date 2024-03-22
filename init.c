/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:17:33 by mateo             #+#    #+#             */
/*   Updated: 2024/03/22 15:20:52 by mateo            ###   ########.fr       */
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

void	ft_parse_map_error(t_fdf *fdf, char **split, char *error, int free_map) // build in e.g., if fd != -1, close fd; must make sure after normal close, that set fd to -1 so dont try to reclose
{
	close(fdf->map_fd);
	get_next_line(fdf->map_height, 1);
	ft_free_arrstr(split);
	ft_free_fdf(fdf, free_map);
	ft_error(error);
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
	if (fdf->map_height_fd == -1)
	{
		close(fdf->map_height_fd);
		ft_parse_map_error(fdf, split, ERR_MALLOC_BUF, -2);
	}
	buffer[4] = '\0';
	r = 1;
	while (r > 0)
	{
		r = read(fdf->map_height_fd, buffer, 4);
		if (r > 0)
			height += ft_nl_read(buffer);
	}
	free(buffer);
	if (r < -1)
	{
		close(fdf->map_height_fd);
		ft_parse_map_error(fdf, split, ERR_READ, -2);
	}
	if (close(fdf->map_height_fd) == -1)
		ft_parse_map_error(fdf, split, ERR_CLOSE, -2);
	return (height);
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

/* ft_not_base checks where str contains characters that are not in base */
int	ft_not_base(char *str, char *base) // check whether duplicates sth needed for atoi_base?
{
	while (*str)
	{
		if (ft_strchr(base, *str) == 0)
			return (1);
		str++;
	}
	return (0);
}

/* ft_check_colour checks if the colour is formatted properly
	- starts with "0x"
	- number is made of 6
	- number is made of hex characters */
int	ft_check_colour(char *str)
{
	int		i;
	char	*nl;

	i = 0;
	if (str[0] != '0' || str[1] != 'x')
		return (0);
	nl = ft_strchr(&str[2], '\n');
	if (nl)
		*nl = '\0';
	if (ft_strlen(&str[2]) != 6)
		return (0);
	if (ft_not_base(&str[2], "0123456789ABCDEF") == 1)
		return (0);
	return (1);
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

/* ft_strisnum checks whether str is made up of digits 
	(until a null terminator or a comma) */
int	ft_strisnum(char *str)
{
	if (*str == '\0' || *str == '\n')
		return (0);
	while (*str && *str != ',' && *str != '\n')
	{
		if (ft_isdigit(*str) == 1 || *str == '-')
			str++;
		else
			return (0);
	}
	return (1);
}

/* ft_fill_pt parses array of str into array of t_pt 
	- frees split after parsing */
t_pt	*ft_fill_pt(t_fdf *fdf, char **split, int y)
{
	int		x;
	t_pt	*row;

	row = malloc(sizeof(t_pt) * fdf->map_width);
	if (!row)
	{
		close(fdf->map_fd);
		ft_free_arrstr(split);
		ft_free_fdf(fdf, y - 1);
		ft_error(ERR_MALLOC_ROW);
	}
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
			close(fdf->map_fd);
			ft_free_arrstr(split);
			ft_free_fdf(fdf, y - 1);
			ft_error(ERR_FILE);
		}
		row[x].colour = ft_map_colour(split, row, x, fdf);
		x++;
	}
	ft_free_arrstr(split);
	return (row);
}

/*	ft_check_fdf checks that the file ends with .fdf */
int	ft_check_fdf(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	i--;
	if (file[i] == 'f' && file[i - 1] == 'd' \
		&& file[i - 2] == 'f' && file[i - 3] == '.')
		return (1);
	return (0);
}

/*	ft_parse_line0 parses the first line of fdf file
	- adds height and width into fdf */
void	ft_parse_line0(char *file, t_fdf *fdf)
{
	char	*line;
	char	**split;

	line = get_next_line(fdf->map_fd, 0);
	if (!line)
	{
		close(fdf->map_fd);
		ft_free_fdf(fdf, -2);
		ft_error(ERR_FILE);
	}
	split = ft_split(line, ' ');
	free(line);
	fdf->map_height = ft_map_height(file, split, fdf);
	fdf->map = malloc(sizeof(t_pt *) * fdf->map_height);
	if (!fdf->map)
	{
		close(fdf->map_fd);
		ft_free_arrstr(split);
		ft_free_fdf(fdf, -2);
		ft_error(ERR_MALLOC_MAP);
	}
	fdf->map_width = ft_count_split(split);
	fdf->map[0] = ft_fill_pt(fdf, split, 0);
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
		split = ft_split(line, ' ');
		free(line);
		if (ft_count_split(split) == fdf->map_width)
		{
			fdf->map[y] = ft_fill_pt(fdf, split, y);
			y++;
		}
		else
		{
			close(fdf->map_fd);
			ft_free_arrstr(split);
			ft_free_fdf(fdf, y - 1);
			ft_error(ERR_FILE);
		}
	}
}

void	ft_init_map(t_fdf *fdf)
{
	fdf->map_fd = -1;
	fdf->map_height_fd = -1;
	fdf->map_width = -1;
	fdf->map_height = -1;
}

/*	ft_parse_map parses the fdf file into array of pt*/
void	ft_parse_map(t_fdf *fdf, char *file)
{
	if (ft_check_fdf(file) == 0)
	{
		ft_free_fdf(fdf, -2);
		ft_error(ERR_EXT);
	}
	ft_init_map(fdf);
	fdf->map_fd = open(file, O_RDONLY);
	if (fdf->map_fd == -1)
	{
		ft_free_fdf(fdf, -2);
		ft_error(ERR_OPEN);
	}
	ft_parse_line0(file, fdf);
	ft_parse_lines(fdf);
	if (close(fdf->map_fd) == -1)
	{
		ft_free_fdf(fdf, fdf->map_height - 1);
		ft_error(ERR_CLOSE);
	}
}

/*	ft_init_transform initialises transformation values in fdf struct*/
void	ft_init_transform(t_fdf *fdf)
{
	fdf->zoom = ft_min((WIDTH - MENU) / fdf->map_width / 2, \
		HEIGHT / fdf->map_height / 2);
	fdf->x_angle = 0;
	fdf->y_angle = 0;
	fdf->z_angle = 0;
	fdf->x_shift = 0;
	fdf->y_shift = 0;
	fdf->project = 0;
	fdf->space = 0;
}

/*	ft_init_mlx initialises the pointers and values associated with mlx */
void	ft_init_mlx(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
	{
		ft_free_fdf(fdf, fdf->map_height - 1);
		ft_error(ERR_MLX);
	}
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "fdf");
	if (!fdf->win)
	{
		ft_free_fdf(fdf, fdf->map_height - 1);
		ft_error(ERR_WIN);
	}
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->img)
	{
		mlx_destroy_window(fdf->mlx, fdf->win);
		ft_free_fdf(fdf, fdf->map_height - 1);
		ft_error(ERR_IMG);
	}
	fdf->data_addr = mlx_get_data_addr(fdf->img, &fdf->bpp, \
		&fdf->size_line, &fdf->endian);
}

/*	ft_init sets up the fdf struct*/
t_fdf	*ft_init(char *file)
{
	t_fdf	*fdf;

	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		ft_error(ERR_MALLOC_FDF);
	ft_parse_map(fdf, file);
	ft_init_mlx(fdf);
	ft_init_transform(fdf);
	return (fdf);
}
