/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:17:24 by mateo             #+#    #+#             */
/*   Updated: 2024/03/22 15:21:07 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*	ft_rotate_x applies rotation matrix for x on 3D coordinates */
void	ft_rotate_x(int *y, int *z, double x_angle)
{
	int	ori_y;

	ori_y = *y;
	*y = ori_y * cos(x_angle) - (*z) * sin(x_angle);
	*z = ori_y * sin(x_angle) + (*z) * cos(x_angle);
}

/*	ft_rotate_y applies rotation matrix for y on 3D coordinates */
void	ft_rotate_y(int *x, int *z, double y_angle)
{
	int	ori_x;

	ori_x = *x;
	*x = ori_x * cos(y_angle) + (*z) * sin(y_angle);
	*z = -ori_x * sin(y_angle) + (*z) * cos(y_angle);
}

/*	ft_rotate_z applies rotation matrix for z on 3D coordinates */
void	ft_rotate_z(int *x, int *y, double z_angle)
{
	int	ori_x;

	ori_x = *x;
	*x = ori_x * cos(z_angle) - (*y) * sin(z_angle);
	*y = ori_x * sin(z_angle) + (*y) * cos(z_angle);
}

/*	ft_iso applies rotation matrices to coordinates for isometric projection
	- rotates around y by 45 degrees
	- rotates around x by ~35 degrees*/
void	ft_iso(t_pt *pt)
{
	pt->x = 1 / sqrt(6) * (sqrt(3) * pt->x - sqrt(3) * pt->z);
	pt->y = 1 / sqrt(6) * (pt->x + 2 * pt->y + pt->z);
	pt->z = 1 / sqrt(6) * (sqrt(2) * pt->x - sqrt(2) * pt->y + sqrt(2) * pt->z);
}

/*	ft_transform projects the 3D coordinates to 2D and applies transformations:
	- scaling map (using zoom)
	- rotating map
	- centering map
	- shifting map
	*/
t_pt	*ft_transform(t_pt point, t_fdf *fdf)
{
	t_pt	*new_pt;

	new_pt = malloc(sizeof(t_pt));
	if (!new_pt)
	{
		mlx_destroy_image(fdf->mlx, fdf->img);
		mlx_destroy_window(fdf->mlx, fdf->win);
		ft_free_fdf(fdf, fdf->map_height - 1);
		ft_error(ERR_MALLOC_NPT);
	}
	new_pt->x = point.x * fdf->zoom;
	new_pt->y = point.y * fdf->zoom;
	new_pt->z = point.z * fdf->zoom;
	ft_rotate_x(&new_pt->y, &new_pt->z, fdf->x_angle);
	ft_rotate_y(&new_pt->x, &new_pt->z, fdf->y_angle);
	ft_rotate_z(&new_pt->x, &new_pt->y, fdf->z_angle);
	if (fdf->project == 0)
		ft_iso(new_pt);
	new_pt->x += (WIDTH - (fdf->map_width * fdf->zoom)) / 2;// replace map_width here with transformed map width 
	new_pt->y += (HEIGHT - (fdf->map_height * fdf->zoom)) / 2;// replace map_width here with transformed map width (need to reorder zoom?)
	new_pt->x += fdf->x_shift;
	new_pt->y += fdf->y_shift;
	new_pt->colour = point.colour;
	return (new_pt);
}

/*	ft_put_pixel places a pt in the img:
	- its place in img determined by x and y
	- colour determined by pt->colour
	- colour placed with little endian format*/
void	ft_put_pixel(t_pt *pt, t_fdf *fdf)	// need to check for endian?
{
	int	i;

	if (pt->x >= MENU && pt->x < WIDTH && pt->y >= 0 && pt->y < HEIGHT)
	{
		i = (pt->x * fdf->bpp / 8) + (pt->y * fdf->size_line);
		fdf->data_addr[i++] = pt->colour;
		fdf->data_addr[i++] = pt->colour >> 8;
		fdf->data_addr[i++] = pt->colour >> 16;
	}
}

/*	ft_gradient picks colour for points on line
	based on how far a point is between start and end */
int	ft_gradient(t_pt *start, t_pt *end, t_pt *temp)
{
	int	percent;
	int	blue;
	int	green;
	int	red;

	if (start->colour == end->colour)
		return (start->colour);
	if (start->x == end->x)
		return (start->colour);
	percent = (temp->x - start->x) / (end->x - start->x);
	blue = (1 - percent) * (start->colour & 0xFF) + \
		percent * (end->colour & 0xFF);
	green = (1 - percent) * ((start->colour >> 8) & 0xFF) \
		+ percent * ((end->colour >> 8) & 0xFF);
	red = (1 - percent) * ((start->colour >> 16) & 0xFF) \
		+ percent * ((end->colour >> 16) & 0xFF);
	return ((red << 16) | (green << 8) | blue);
}

/*	ft_line_setup sets up for ft_line
	- swap start and end if end comes before start (in x)
	- create and return temp pt to hold points along the line */
t_pt	*ft_line_setup(t_pt **start, t_pt **end, t_fdf *fdf)
{
	t_pt	*temp;

	if ((*start)->x > (*end)->x)
	{
		temp = *start;
		*start = *end;
		*end = temp;
	}
	temp = malloc(sizeof(t_pt));
	if (!temp)
	{
		mlx_destroy_image(fdf->mlx, fdf->img);
		mlx_destroy_window(fdf->mlx, fdf->win);
		free(start);
		free(end);
		ft_free_fdf(fdf, fdf->map_height - 1);
		ft_error(ERR_MALLOC_TPT);
	}
	temp->x = (*start)->x;
	temp->y = (*start)->y;
	return (temp);
}

/*	ft_line_gentle implements Bresenham's line algorithm for gentle slopes*/
void	ft_line_gentle(t_pt *start, t_pt *end, t_pt *temp, t_fdf *fdf)
{
	int	dy;
	int	dx;
	int	decision;

	dx = end->x - start->x;
	dy = end->y - start->y;
	decision = 2 * ft_abs(dy) - dx;
	while (temp->x != end->x || temp->y != end->y)
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
		temp->colour = ft_gradient(start, end, temp);
		ft_put_pixel(temp, fdf);
	}
}

/*	ft_line_steep implements Bresenham's line algorithm for steep slopes*/
void	ft_line_steep(t_pt *start, t_pt *end, t_pt *temp, t_fdf *fdf)
{
	int	dy;
	int	dx;
	int	decision;

	dx = end->x - start->x;
	dy = end->y - start->y;
	decision = 2 * dx - ft_abs(dy);
	while (temp->x != end->x || temp->y != end->y)
	{
		if (dy > 0)
			temp->y += 1;
		else if (dy < 0)
			temp->y -= 1;
		if (decision < 0)
			decision += 2 * dx;
		else
		{
			decision += 2 * dx - 2 * ft_abs(dy);
			temp->x += 1;
		}
		temp->colour = ft_gradient(start, end, temp);
		ft_put_pixel(temp, fdf);
	}
}

/*	ft_line implements Bresenham's line algorithm 
	for all slopes and directions*/
void	ft_line(t_pt *start, t_pt *end, t_fdf *fdf)
{
	t_pt	*temp;
	int		dx;
	int		dy;

	temp = ft_line_setup(&start, &end, fdf);
	dx = end->x - start->x;
	dy = end->y - start->y;
	ft_put_pixel(start, fdf);
	if (ft_abs(dy) < dx)
		ft_line_gentle(start, end, temp, fdf);
	else
		ft_line_steep(start, end, temp, fdf);
	free(start);
	free(end);
	free(temp);
}

/*	ft_menu places menu instructions in window on LHS */
void	ft_menu(t_fdf *fdf)
{
	int	c;

	c = DEFAULT_COLOUR;
	mlx_string_put(fdf->mlx, fdf->win, 10, 10, c, "Instructions");
	mlx_string_put(fdf->mlx, fdf->win, 10, 50, c, "Close: Esc");
	mlx_string_put(fdf->mlx, fdf->win, 10, 80, c, "Rotate X: Q / W");
	mlx_string_put(fdf->mlx, fdf->win, 10, 110, c, "Rotate Y: A / S");
	mlx_string_put(fdf->mlx, fdf->win, 10, 140, c, "Rotate Z: Z / X");
	mlx_string_put(fdf->mlx, fdf->win, 10, 170, c, "Move: Arrow Keys");
	mlx_string_put(fdf->mlx, fdf->win, 10, 200, c, "Zoom: + / -");
	mlx_string_put(fdf->mlx, fdf->win, 10, 230, c, "Isometric: 1");
	mlx_string_put(fdf->mlx, fdf->win, 10, 260, c, "Parellel: 2 - 7");
	mlx_string_put(fdf->mlx, fdf->win, 10, 290, c, "Spin: Hold Space");
}

/*	ft_draw:
	- resets the window to black
	- plots each transformed point and its lines into img
	- sends the image to window
	- draws the menu in window */
int	ft_draw(t_fdf *fdf)
{
	int	x;
	int	y;

	ft_bzero(fdf->data_addr, WIDTH * HEIGHT * (fdf->bpp / 8));
	y = 0;
	while (y < fdf->map_height)
	{
		x = 0;
		while (x < fdf->map_width)
		{
			if (x != fdf->map_width - 1)
				ft_line(ft_transform(fdf->map[y][x], fdf), \
					ft_transform(fdf->map[y][x + 1], fdf), fdf);
			if (y != fdf->map_height - 1)
				ft_line(ft_transform(fdf->map[y][x], fdf), \
					ft_transform(fdf->map[y + 1][x], fdf), fdf);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	ft_menu(fdf);
	return (0);
}
