/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:14:12 by mateo             #+#    #+#             */
/*   Updated: 2024/03/11 07:01:03 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H

#include "mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>

# define ERR_ARGC		"Usage: ./fdf <filename>"
# define ERR_MALLOC_FDF	"Error allocating for fdf"
# define ERR_MALLOC_MAP "Error allocating for map"
# define ERR_OPEN		"Error opening file"
# define ERR_MLX		"Error connecting to X server"
# define ERR_WIN 		"Error creating window"

typedef struct	s_map
{
	int	x;
	int	y;
}	t_map;

typedef	struct	s_fdf
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*data_addr;
	t_map	*map;
}

/*init.c*/

/*utils.c*/
void	ft_error(char *str);

#endif