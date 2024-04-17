/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 06:00:33 by mateo             #+#    #+#             */
/*   Updated: 2024/04/17 13:59:00 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*	ft_abs returns absolute value of int*/
int	ft_abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

/*	ft_min returns the minimum of two doubles*/
double	ft_min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

/*	key_num returns 1 if a number key was pressed;
	0 otherwise */
int	key_num(int key)
{
	if (key == KEY_ONE || key == KEY_TWO || key == KEY_THREE || \
		key == KEY_FOUR || key == KEY_FIVE || key == KEY_SIX || \
		key == KEY_SEVEN || key == KEY_NP_ONE || key == KEY_NP_TWO || \
		key == KEY_NP_THREE || key == KEY_NP_FOUR || key == KEY_NP_FIVE \
		|| key == KEY_NP_SIX || key == KEY_NP_SEVEN)
		return (1);
	return (0);
}
