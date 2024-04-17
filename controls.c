/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:09:33 by mateo             #+#    #+#             */
/*   Updated: 2024/04/17 14:00:33 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*	ft_rotate updates angle values in fdf for specific keypress*/
void	ft_rotate(int key, t_fdf *fdf)
{
	if (key == KEY_Q)
		fdf->x_angle += M_PI / 12;
	else if (key == KEY_W)
		fdf->x_angle -= M_PI / 12;
	else if (key == KEY_A)
		fdf->y_angle += M_PI / 12;
	else if (key == KEY_S)
		fdf->y_angle -= M_PI / 12;
	else if (key == KEY_Z)
		fdf->z_angle += M_PI / 12;
	else if (key == KEY_X)
		fdf->z_angle -= M_PI / 12;
	ft_draw(fdf);
}

/*	ft_move updates shift values in fdf for specific keypress*/
void	ft_move(int key, t_fdf *fdf)
{
	if (key == KEY_UP)
		fdf->y_shift -= 5;
	else if (key == KEY_DOWN)
		fdf->y_shift += 5;
	else if (key == KEY_RIGHT)
		fdf->x_shift += 5;
	else if (key == KEY_LEFT)
		fdf->x_shift -= 5;
	ft_draw(fdf);
}

/*	ft_project updates project and angle values in fdf for specific keypress*/
void	ft_project(int key, t_fdf *fdf)
{
	ft_init_transform(fdf);
	if (key != KEY_ONE && key != KEY_NP_ONE)
		fdf->project = 1;
	if (key == KEY_THREE || key == KEY_NP_THREE)
		fdf->y_angle = M_PI / 2;
	else if (key == KEY_FOUR || key == KEY_NP_FOUR)
		fdf->y_angle = M_PI;
	else if (key == KEY_FIVE || key == KEY_NP_FIVE)
		fdf->y_angle = 3 * M_PI / 2;
	else if (key == KEY_SIX || key == KEY_NP_SIX)
		fdf->x_angle = M_PI / 2;
	else if (key == KEY_SEVEN || key == KEY_NP_SEVEN)
		fdf->x_angle = -M_PI / 2;
	ft_draw(fdf);
}

/*	ft_zoom updates zoom values in fdf for specific keypress*/
void	ft_zoom(int key, t_fdf *fdf)
{
	if (key == KEY_PLUS || key == KEY_NP_PLUS)
		fdf->zoom += 0.5;
	else if (key == KEY_MINUS || key == KEY_NP_MINUS)
		fdf->zoom -= 0.5;
	ft_draw(fdf);
}

/*	ft_key directs specific keypresses to various actions
	- close
	- rotate
	- move
	- project
	- zoom
	and updates values for keyholds (space and C) */
int	ft_key(int key, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	ft_putnbr_fd(key, 1);
	ft_putchar_fd('\n', 1);
	if (key == KEY_ESC)
		ft_close(fdf);
	else if (key == KEY_Q || key == KEY_W || key == KEY_A \
		|| key == KEY_S || key == KEY_Z || key == KEY_X)
		ft_rotate(key, fdf);
	else if (key == KEY_UP || key == KEY_DOWN || \
		key == KEY_RIGHT || key == KEY_LEFT)
		ft_move(key, fdf);
	else if (key_num(key) == 1)
		ft_project(key, fdf);
	else if (key == KEY_PLUS || key == KEY_MINUS \
	|| key == KEY_NP_PLUS || key == KEY_NP_MINUS)
		ft_zoom(key, fdf);
	else if (key == KEY_SPACE)
		fdf->space = 1;
	else if (key == KEY_C)
		fdf->colour_change = 1;
	return (0);
}
