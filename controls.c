/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:09:33 by mateo             #+#    #+#             */
/*   Updated: 2024/03/17 19:25:36 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int key, void *param)
{
	if (key == MAIN_PAD_ESC)	// check key codes on Mac
	{
		exit
	}
}

void	ft_controls(t_fdf *fdf)
{
	mlx_key_hook(fdf->win, ft_key, fdf);
}