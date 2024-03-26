/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:17:24 by mateo             #+#    #+#             */
/*   Updated: 2024/03/26 16:12:59 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"



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
	if (fdf->colour_change == 0)
		new_pt->colour = point.colour;
	else
		new_pt->colour = ft_change_colour(point.colour);
	return (new_pt);
}

/*	ft_put_pixel places a pt in the img:
	- its place in img determined by x and y
	- colour determined by pt->colour
	- colour placed with little endian format*/
void	ft_put_pixel(t_pt *pt, t_fdf *fdf)
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
	mlx_string_put(fdf->mlx, fdf->win, 10, 320, c, "Change Colour: Hold C");
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
