/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:17:18 by mateo             #+#    #+#             */
/*   Updated: 2024/03/18 10:18:44 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_line(t_pt *pt_a, t_pt *pt_b, t_fdf *fdf) // how to adapt bresenham's algorithm for any pair of points e.g., different slope; reverse direction
{
	t_pt	*start;
	t_pt	*end;
	int		dx;
	int		dy;
	int		decision;

	start = pt_a;
	end = pt_b;
	if (pt_a->x > pt_b->x)
	{
		start = pt_b;
		end = pt_a;
	}
	dx = end->x - start->x;
    dy = end->y - start->y;
	
    ft_put_pixel(start, fdf); 
    while (start->x != end->x || start->y != end->y) {

		if (ft_abs(dy) < fd_abs(dx))
		{
			decision = 2 * ft_abs(dy) - ft_abs(dx);
			
			
		}

    	ft_put_pixel(pt_a, fdf); // write this function
		
    }
	free(pt_a);
	free(pt_b);
}
