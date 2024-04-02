/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:15:38 by mateo             #+#    #+#             */
/*   Updated: 2024/04/02 19:33:06 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* ft_not_base checks where str contains characters that are not in base */
int	ft_not_base(char *str, char *base)
{
	while (*str)
	{
		if (ft_strchr(base, *str) == 0)
			return (1);
		str++;
	}
	return (0);
}

/* ft_check_colour checks if the colour is formatted properly
	- starts with "0x"
	- number is made of 6
	- number is made of hex characters */
int	ft_check_colour(char *str)
{
	int		i;
	char	*nl;

	i = 0;
	if (str[0] != '0' || str[1] != 'x')
		return (0);
	nl = ft_strchr(&str[2], '\n');
	if (nl)
		*nl = '\0';
	if (ft_strlen(&str[2]) != 6)
		return (0);
	if (ft_not_base(&str[2], "0123456789ABCDEFabcdef") == 1)
		return (0);
	return (1);
}

/* ft_strisnum checks whether str is made up of digits 
	(until a null terminator or a comma) */
int	ft_strisnum(char *str)
{
	if (*str == '\0')
		return (1);
	while (*str && *str != ',' && *str != '\n' && *str != ' ')
	{
		if (ft_isdigit(*str) == 1 || *str == '-')
			str++;
		else
			return (0);
	}
	return (1);
}

/*	ft_check_fdf checks that the file ends with .fdf */
int	ft_check_fdf(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	i--;
	if (file[i] == 'f' && file[i - 1] == 'd' \
		&& file[i - 2] == 'f' && file[i - 3] == '.')
		return (1);
	return (0);
}
