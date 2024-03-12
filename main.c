/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:14:06 by mateo             #+#    #+#             */
/*   Updated: 2024/03/12 15:45:08 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	*fdf;
	if (argc == 2)
	{
		fdf = ft_init(argv[1]);	// need to free fdf
		mlx_loop(fdf->mlx);
		
	}
	else
		ft_error(ERR_ARGC, -1);
	return (0);	
}
