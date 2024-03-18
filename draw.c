/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:17:24 by mateo             #+#    #+#             */
/*   Updated: 2024/03/18 12:52:39 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_rotate_x(int *y, int *z, t_pt point, double x_angle)
{
	*y = point.y * cos(x_angle) - point.z * sin(x_angle);
	*z = point.y * sin(x_angle) + point.z* cos(x_angle);
}

void	ft_rotate_y(int *x, int *z, t_pt point, double y_angle)
{
	*x = point.x * cos(y_angle) + point.z * sin(y_angle);
	*z = -point.x * sin(y_angle) + point.z * cos(y_angle); 
}

void	ft_rotate_z(int *x, int *y, t_pt point, double z_angle)
{
	*x = point.x * cos(z_angle) - (point.y) * sin(z_angle);
	*y = point.x * sin(z_angle) + (point.y) * cos(z_angle);
}

t_pt	*ft_project(t_pt point, t_fdf *fdf)
{
	t_pt	*new_pt;

	new_pt = malloc(sizeof(t_pt));
	if (!new_pt)
	{
		ft_free_fdf(fdf, fdf->map_height - 1);
		ft_error(ERR_MALLOC_NPT);
	}
	ft_rotate_x(&new_pt->y, &new_pt->z, point, fdf->x_angle);
	ft_rotate_y(&new_pt->x, &new_pt->z, point, fdf->y_angle);
	ft_rotate_z(&new_pt->x, &new_pt->y, point, fdf->z_angle);
	new_pt->colour = point->colour;
	return (new_pt);
}

int ft_abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

void	ft_put_pixel(t_pt *pt, t_fdf *fdf)
{
	int	i;
	
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) // what if out of bounds?
	{
		i = (pt->x * fdf->bits_per_pixel / 8) + (pt->y * fdf->size_line);
		fdf->data_arr[i++] = pt->colour;
		fdf->data_arr[i++] = pt->colour >> 8;
		fdf->data_arr[i++] = pt->colour >> 16;
	}
}

int	ft_gradient(t_pt *start, t_pt *end, t_pt *temp)
{
	int percent;
	
	if (start->colour == end->colour)
		return (start->colour);
	percent = (100 * (temp->x - start->x)) / (end->x - start->x);
	blue = (1 - percent) * (start->colour & 0xFF) + percent * (end->colour & 0xFF);
	green = (1 - percent) * ((start->colour >> 8) & 0xFF) + percent * ((end->colour >> 8) & 0xFF);
	red = (1 - percent) * ((start->colour >> 16) & 0xFF) + percent * ((end->colour >> 16) & 0xFF);
	return ((red << 16) | (green << 8) | blue);
}

void	ft_line(t_pt *start, t_pt *end, t_fdf *fdf)
{
	t_pt *temp;
	int	dx;
	int dy;
	int decision;

	if (start->x > end->x)
	{
		temp = start;
		start = end;
		end = temp;
	}
	temp = malloc(sizeof(t_pt));
	if (!temp)
	{
		free(start);
		free(end);
		ft_free_fdf(fdf, fdf->map_height - 1);
		ft_error(ERR_MALLOC_TPT);
	}
	temp->x = start->x;
	temp->y = start->y;
	temp->z = start->z;
	
	dx = end->x - start->x;
    dy = end->y - start->y;
	
	// // check that computation for dy = dx works? dy = 0? dx = 0?
	if (ft_abs(dy) < dx)
		decision = 2 * ft_abs(dy) - dx;
	else
		decision = 2 * dx - ft_abs(dy);
    ft_put_pixel(start, fdf);
    while (temp->x != end->x || temp->y != end->y) {

		if (ft_abs(dy) < dx)
		{
			temp->x += 1;
			if (decision < 0)
				decision += 2 * ft_abs(dy);
			else
			{
				decision += 2 * ft_abs(dy) - 2 * dx;
				if (dy > 0)
					temp->y += 1;
				else if (dy < 0)
					temp->y -= 1;
			}
		}
		else
		{
			temp->y += 1;
			if (decision < 0)
				decision += 2 * dx;
			else
			{
				decision += 2 * dx - 2 * ft_abs(dy);
				temp->x += 1;
			}
		}
		temp->colour = ft_gradient(start, end, temp);
    	ft_put_pixel(temp, fdf);
    }
	free(start);
	free(end);
	free(temp);
}
    
void	ft_draw(t_fdf *fdf)
{
	int	x;
	int	y;
	
	ft_bzero(fdf->data_addr, WIDTH * HEIGHT * (fdf->bits_per_pixel / 8));
	y = 0;
	while (y < fdf->map_height)
	{
		x = 0;
		while (x < fdf->map_width)
		{
			if (x != fdf->map_width - 1)
				ft_line(ft_project(fdf->map[y][x], fdf), ft_project(fdf->map[y][x + 1], fdf), fdf);
			if (y != fdf->map_height - 1)
				ft_line(ft_project(fdf->map[y][x], fdf), ft_project(fdf->map[y + 1][x], fdf), fdf);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}