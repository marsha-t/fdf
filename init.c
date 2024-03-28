/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:17:33 by mateo             #+#    #+#             */
/*   Updated: 2024/03/28 13:51:16 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	fdf->colour_change = 0;
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
