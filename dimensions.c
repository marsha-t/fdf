/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dimensions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:49:50 by mateo             #+#    #+#             */
/*   Updated: 2024/04/02 07:21:43 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*	ft_update_new projects points and calculates width and height of the projection
	t_dim *points is freed */
void	ft_update_new(t_fdf *fdf, t_dim *points)
{
	fdf->x_min = (1 / sqrt(6)) * (sqrt(3) * points->x_min->x * \
		fdf->zoom - sqrt(3) * points->x_min->z * fdf->zoom);
	fdf->x_max = (1 / sqrt(6)) * (sqrt(3) * points->x_max->x * \
		fdf->zoom - sqrt(3) * points->x_max->z * fdf->zoom);
	fdf->y_min = (1 / sqrt(6)) * (points->y_min->x * fdf->zoom \
		+ 2 * points->y_min->y * fdf->zoom + points->y_min->z * fdf->zoom);
	fdf->y_max = (1 / sqrt(6)) * (points->y_max->x * fdf->zoom \
		+ 2 * points->y_max->y * fdf->zoom + points->y_max->z * fdf->zoom);
	fdf->new_width = fdf->x_max - fdf->x_min;
	fdf->new_height = fdf->y_max - fdf->y_min;
	free(points);
}

/*	ft_init_points initialises the t_dim *points */
t_dim	*ft_init_points(void)
{
	t_dim	*points;

	points = malloc(sizeof(t_dim));
	points->min_sum_x = INT_MAX;
	points->max_sum_x = INT_MIN;
	points->max_sum_y = INT_MIN;
	points->min_sum_y = INT_MAX;
	return (points);
}

/*	ft_find_minmax finds points in original map 
	that will give the min and max of x and y after isometric transformation */
void	ft_find_minmax(int x, int y, t_fdf *fdf, t_dim *points)
{
	if (x - fdf->map[y][x].z < points->min_sum_x)
	{
		points->min_sum_x = x - fdf->map[y][x].z;
		points->x_max = &fdf->map[y][x];
	}
	if (x - fdf->map[y][x].z > points->max_sum_x)
	{
		points->max_sum_x = x - fdf->map[y][x].z;
		points->x_min = &fdf->map[y][x];
	}
	if (x + 2 * y + fdf->map[y][x].z < points->min_sum_y)
	{
		points->min_sum_y = x + 2 * y + fdf->map[y][x].z;
		points->y_min = &fdf->map[y][x];
	}
	if (x + 2 * y + fdf->map[y][x].z > points->max_sum_y)
	{
		points->max_sum_y = x + 2 * y + fdf->map[y][x].z;
		points->y_max = &fdf->map[y][x];
	}
}

/*	ft_update_dimensions updates the values of new_width and new_height */
void	ft_update_dimensions(t_fdf *fdf)
{
	int		y;
	int		x;
	t_dim	*points;

	points = ft_init_points();
	if (fdf->project == 0)
	{
		y = 0;
		while (y < fdf->map_height)
		{
			x = 0;
			while (x < fdf->map_width)
			{
				ft_find_minmax(x, y, fdf, points);
				x++;
			}
			y++;
		}
		ft_update_new(fdf, points);
	}
}
