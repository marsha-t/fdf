/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:12:09 by mateo             #+#    #+#             */
/*   Updated: 2024/03/28 12:49:13 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_change_colour(int colour)
{
	int	blue;
	int	green;
	int	red;

	blue = 255 - (colour & 0xFF);
	green = 255 - ((colour >> 8) & 0xFF);
	red = 255 - ((colour >> 16) & 0xFF);
	return ((red << 16) | (green << 8) | blue);
}

/*	ft_gradient picks colour for points on line
	based on how far a point is between start and end */
int	ft_gradient(t_pt *start, t_pt *end, t_pt *temp)
{
	int	percent;
	int	blue;
	int	green;
	int	red;

	if (start->colour == end->colour)
		return (start->colour);
	if (start->x == end->x)
		return (start->colour);
	percent = (temp->x - start->x) / (end->x - start->x);
	blue = (1 - percent) * (start->colour & 0xFF) + \
		percent * (end->colour & 0xFF);
	green = (1 - percent) * ((start->colour >> 8) & 0xFF) \
		+ percent * ((end->colour >> 8) & 0xFF);
	red = (1 - percent) * ((start->colour >> 16) & 0xFF) \
		+ percent * ((end->colour >> 16) & 0xFF);
	return ((red << 16) | (green << 8) | blue);
}
