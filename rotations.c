/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:09:43 by mateo             #+#    #+#             */
/*   Updated: 2024/03/26 16:10:16 by mateo            ###   ########.fr       */
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
