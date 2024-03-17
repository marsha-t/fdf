/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 06:38:17 by mateo             #+#    #+#             */
/*   Updated: 2024/03/17 10:27:08 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* ft_free_arrstr frees an array of strings */
void	ft_free_arrstr(char **split)
{
	int	i;	

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/* ft_free_fdf frees fdf as well as fdf->map
	- free_map = -2: only free fdf
	- free_map = -1: free fdf and fdf->map
	- free_map > -1: free fdf, fdf->map and free_map rows of fdf->map 
		(including free_map = 0 i.e., the first row)*/
void	ft_free_fdf(t_fdf *fdf, int free_map)
{
	int	h;
	
	if (free_map >= 0)
	{
		h = 0;
		while (h <= free_map)
		{
			free(fdf->map[h]);
			h++;
		}
	}
	if (free_map >= -1)
		free(fdf->map);
	free(fdf);
}

void	ft_error(char *str)
{
	if (errno == 0)
	{
		ft_putendl_fd(str, 2);
	}
	else
	{
		perror(str);
	}
	exit(1);
}