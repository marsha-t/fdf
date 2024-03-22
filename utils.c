/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 06:00:33 by mateo             #+#    #+#             */
/*   Updated: 2024/03/22 06:34:37 by mateo            ###   ########.fr       */
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

/*	ft_min returns the minimum of two int*/
int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

/*	ft_max returns the maximum of two int*/
int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
