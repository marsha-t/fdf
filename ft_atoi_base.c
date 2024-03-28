/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:45:18 by mateo             #+#    #+#             */
/*   Updated: 2024/03/28 16:13:33 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_base_ok(char *base)
{
	int		i;
	size_t	j;

	if (ft_strlen(base) == 0 || ft_strlen(base) == 1)
		return (0);
	i = 0;
	while (base[i] != '\0')
	{
		if ((base[i] == '+') || (base[i] == '-') \
		|| (base[i] < 32) || (base[i] > 126))
			return (0);
		j = i + 1;
		while (j < ft_strlen(base) - 1)
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_c_is_whitespace(char c)
{
	if ((c == ' ' || c == '\n' || c == '\t' || \
	c == '\v' || c == '\f' || c == '\r'))
		return (1);
	return (0);
}

int	ft_c_is_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	int	i;
	int	r;
	int	s;

	s = 1;
	r = 0;
	if (ft_base_ok(base) == 1)
	{
		i = 0;
		while (ft_c_is_whitespace(str[i]) == 1)
			i++;
		while ((str[i] == '+') || (str[i] == '-'))
		{
			if (str[i] == '-')
				s = -s;
			i++;
		}
		while (ft_c_is_base(str[i], base) > -1)
			r = (r * ft_strlen(base)) + (ft_c_is_base(str[i++], base));
	}
	return (r * s);
}
