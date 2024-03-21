/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:14:06 by mateo             #+#    #+#             */
/*   Updated: 2024/03/21 17:17:31 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc == 2)
	{
		fdf = ft_init(argv[1]);
		ft_draw(fdf);
		mlx_loop_hook(fdf->mlx, ft_draw, fdf);
		mlx_key_hook(fdf->win, ft_key, fdf);
		mlx_hook(fdf->win, 17, 0, ft_close, fdf);
		mlx_loop(fdf->mlx);
	}
	else
		ft_error(ERR_ARGC);
	return (0);
}
