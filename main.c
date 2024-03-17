/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:14:06 by mateo             #+#    #+#             */
/*   Updated: 2024/03/16 07:09:36 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	*fdf;
	if (argc == 2)
	{
		printf("here\n");
		fdf = ft_init(argv[1]);
		mlx_loop(fdf->mlx);
		// mlx_destroy_image() // when should this be destroyed?
		mlx_destroy_window(fdf->mlx, fdf->win);
		ft_free_fdf(fdf, fdf->map_height);

	}
	else
		ft_error(ERR_ARGC);
	return (0);	
}

