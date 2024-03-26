/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:07:04 by mateo             #+#    #+#             */
/*   Updated: 2024/03/26 16:08:18 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*	ft_line_setup sets up for ft_line
	- swap start and end if end comes before start (in x)
	- create and return temp pt to hold points along the line */
t_pt	*ft_line_setup(t_pt **start, t_pt **end, t_fdf *fdf)
{
	t_pt	*temp;

	if ((*start)->x > (*end)->x)
	{
		temp = *start;
		*start = *end;
		*end = temp;
	}
	temp = malloc(sizeof(t_pt));
	if (!temp)
	{
		mlx_destroy_image(fdf->mlx, fdf->img);
		mlx_destroy_window(fdf->mlx, fdf->win);
		free(start);
		free(end);
		ft_free_fdf(fdf, fdf->map_height - 1);
		ft_error(ERR_MALLOC_TPT);
	}
	temp->x = (*start)->x;
	temp->y = (*start)->y;
	return (temp);
}

/*	ft_line_gentle implements Bresenham's line algorithm for gentle slopes*/
void	ft_line_gentle(t_pt *start, t_pt *end, t_pt *temp, t_fdf *fdf)
{
	int	dy;
	int	dx;
	int	decision;

	dx = end->x - start->x;
	dy = end->y - start->y;
	decision = 2 * ft_abs(dy) - dx;
	while (temp->x != end->x || temp->y != end->y)
	{
		temp->x += 1;
		if (decision < 0)
			decision += 2 * ft_abs(dy);
		else
		{
			decision += 2 * ft_abs(dy) - 2 * dx;
			if (dy > 0)
				temp->y += 1;
			else if (dy < 0)
				temp->y -= 1;
		}
		temp->colour = ft_gradient(start, end, temp);
		ft_put_pixel(temp, fdf);
	}
}

/*	ft_line_steep implements Bresenham's line algorithm for steep slopes*/
void	ft_line_steep(t_pt *start, t_pt *end, t_pt *temp, t_fdf *fdf)
{
	int	dy;
	int	dx;
	int	decision;

	dx = end->x - start->x;
	dy = end->y - start->y;
	decision = 2 * dx - ft_abs(dy);
	while (temp->x != end->x || temp->y != end->y)
	{
		if (dy > 0)
			temp->y += 1;
		else if (dy < 0)
			temp->y -= 1;
		if (decision < 0)
			decision += 2 * dx;
		else
		{
			decision += 2 * dx - 2 * ft_abs(dy);
			temp->x += 1;
		}
		temp->colour = ft_gradient(start, end, temp);
		ft_put_pixel(temp, fdf);
	}
}

/*	ft_line implements Bresenham's line algorithm 
	for all slopes and directions*/
void	ft_line(t_pt *start, t_pt *end, t_fdf *fdf)
{
	t_pt	*temp;
	int		dx;
	int		dy;

	temp = ft_line_setup(&start, &end, fdf);
	dx = end->x - start->x;
	dy = end->y - start->y;
	ft_put_pixel(start, fdf);
	if (ft_abs(dy) < dx)
		ft_line_gentle(start, end, temp, fdf);
	else
		ft_line_steep(start, end, temp, fdf);
	free(start);
	free(end);
	free(temp);
}
