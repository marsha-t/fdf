#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
	int	x;
	int	y;
	int	z;
	int	colour;
}				t_pt;

t_pt	*ft_project(t_pt point) 
{
	t_pt	*new_pt;
	int zoom = 1;
	int x_shift = 0;
	int y_shift = 0;

	new_pt = malloc(sizeof(t_pt));

	new_pt->x = point.x * zoom;
	new_pt->y = point.y * zoom;
	new_pt->z = point.z * zoom;
	// ft_rotate_x(&new_pt->y, &new_pt->z, fdf->x_angle); // unclear if isometric
	// ft_rotate_y(&new_pt->x, &new_pt->z, fdf->y_angle);
	// ft_rotate_z(&new_pt->x, &new_pt->y, fdf->z_angle);
	new_pt->x += x_shift;
	new_pt->y += y_shift;
	// new_pt->colour = point.colour;
	return (new_pt);
}

int ft_abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}


void	ft_line(t_pt *start, t_pt *end)
{
	t_pt *temp;
	int	dx;
	int dy;
	int decision;

	if (start->x > end->x)
	{
		temp = start;
		start = end;
		end = temp;
	}
	temp = malloc(sizeof(t_pt));
	
	temp->x = start->x;
	temp->y = start->y;
	temp->z = start->z;
	
	dx = end->x - start->x;
    dy = end->y - start->y;
	
	if (ft_abs(dy) < dx)
		decision = 2 * ft_abs(dy) - dx;
	else
		decision = 2 * dx - ft_abs(dy);
    while (temp->x != end->x || temp->y != end->y) {

		if (ft_abs(dy) < dx)
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
		}
		else
		{
			temp->y += 1;
			if (decision < 0)
				decision += 2 * dx;
			else
			{
				decision += 2 * dx - 2 * ft_abs(dy);
				temp->x += 1;
			}
		}
		printf("%d, %d\n", temp->x, temp->y);
    }
	free(temp);
}

int main(void)
{
	t_pt *start;
	t_pt *end;

	start = malloc(sizeof(t_pt));
	end = malloc(sizeof(t_pt));

	// gentle (2, 2, 3, 3, 4, 4, 5)
	// start->x = 1;
	// start->y = 1;
	// end->x = 8;
	// end->y = 5;

	
	// gentle (reverse) (2, 2, 3, 3, 4, 4, 5)
	// start->x = 8;
	// start->y = 5;
	// end->x = 1;
	// end->y = 1;
	
	// exact (2, 3, 4, 5)
	// start->x = 1;
	// start->y = 1;
	// end->x = 5;
	// end->y = 5;

	// exact (reverse) (2, 3, 4, 5)
	// start->x = 5;
	// start->y = 5;
	// end->x = 1;
	// end->y = 1;

	// steep (2, 2, 3, 3, 4, 4, 5)
	// start->x = 1;
	// start->y = 1;
	// end->x = 5;
	// end->y = 8;
	
	// steep (reverse) (2, 2, 3, 3, 4, 4, 5)
	// start->x = 5;
	// start->y = 8;
	// end->x = 1;
	// end->y = 1;

	// vertical (2, 3, 4, 5, 6, 7, 8)
	// start->x = 1;
	// start->y = 1;
	// end->x = 1;
	// end->y = 8;

	// vertical (2, 3, 4, 5, 6, 7, 8)
	// start->x = 1;
	// start->y = 8;
	// end->x = 1;
	// end->y = 1;

	// horizontal (2, 3, 4, 5, 6, 7, 8)
	// start->x = 1;
	// start->y = 1;
	// end->x = 8;
	// end->y = 1;

	// horizontal (2, 3, 4, 5, 6, 7, 8)
	start->x = 1;
	start->y = 1;
	end->x = 8;
	end->y = 1;

	ft_line(start, end);
	// ft_line (ft_project(*start), ft_project(*end));
	free(start);
	free(end);
}
// void	ft_line(t_pt *start, t_pt *end, t_fdf *fdf)
// {
// 	t_pt *temp;
// 	int	dx;
// 	int dy;
// 	int decision;

// 	if (start->x > end->x)
// 	{
// 		temp = start;
// 		start = end;
// 		end = temp;
// 	}
// 	temp = malloc(sizeof(t_pt));
// 	if (!temp)
// 	{
// 		mlx_destroy_image(fdf->mlx, fdf->img);
// 		mlx_destroy_window(fdf->mlx, fdf->win);
// 		free(start);
// 		free(end);
// 		ft_free_fdf(fdf, fdf->map_height - 1);
// 		ft_error(ERR_MALLOC_TPT);
// 	}
// 	temp->x = start->x;
// 	temp->y = start->y;
// 	temp->z = start->z;
	
// 	dx = end->x - start->x;
//     dy = end->y - start->y;
	
// 	// // check that computation for dy = dx works? dy = 0? dx = 0?
// 	if (ft_abs(dy) < dx)
// 		decision = 2 * ft_abs(dy) - dx;
// 	else
// 		decision = 2 * dx - ft_abs(dy);
//     ft_put_pixel(start, fdf);
//     while (temp->x != end->x || temp->y != end->y) {

// 		if (ft_abs(dy) < dx)
// 		{
// 			temp->x += 1;
// 			if (decision < 0)
// 				decision += 2 * ft_abs(dy);
// 			else
// 			{
// 				decision += 2 * ft_abs(dy) - 2 * dx;
// 				if (dy > 0)
// 					temp->y += 1;
// 				else if (dy < 0)
// 					temp->y -= 1;
// 			}
// 		}
// 		else if (ft_abs(dy) > dx) // added condiiton
// 		{
// 			temp->y += 1;
// 			if (decision < 0)
// 				decision += 2 * dx;
// 			else
// 			{
// 				decision += 2 * dx - 2 * ft_abs(dy);
// 				temp->x += 1;
// 			}
// 		}
// 		temp->colour = ft_gradient(start, end, temp); // temp->colour = start->colour; // to test
//     	ft_put_pixel(temp, fdf);
//     }
// 	free(start);
// 	free(end);
// 	free(temp);
// }