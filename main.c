/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:14:06 by mateo             #+#    #+#             */
/*   Updated: 2024/03/26 13:15:44 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*	ft_loop_draw rotates y and draws if space is held down;
	otherwise, it draws*/
int ft_loop_draw(t_fdf *fdf)
{
	if (fdf->space == 0)
		ft_draw(fdf);
	else
	{
		fdf->y_angle += M_PI / 180;
		ft_draw(fdf);
	}
	return (0);
}

/*	ft_keyrelease resets the space indicator to zero once the key has been released*/
int	ft_keyrelease(int key, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (key == KEY_SPACE)
		fdf->space = 0;
	else if (key == KEY_C) // NEW FEATURE
		fdf->colour_change = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc == 2)
	{
		fdf = ft_init(argv[1]);
		ft_draw(fdf);
		mlx_hook(fdf->win, 2, 1L<<0, ft_key, fdf);
		mlx_loop_hook(fdf->mlx, ft_loop_draw, fdf);
		mlx_hook(fdf->win, 17, 0L, ft_close, fdf);
		mlx_hook(fdf->win, 3, 1L<<1, ft_keyrelease, fdf);
		mlx_loop(fdf->mlx);
	}
	else
		ft_error(ERR_ARGC);
	return (0);
}
