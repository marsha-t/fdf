/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 06:38:17 by mateo             #+#    #+#             */
/*   Updated: 2024/03/11 11:22:02 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_error(char *str, int fd)
{
	if (errno == 0)
	{
		ft_putendl_fd(str, 2);
		if (fd >= 0)
			close(fd);
	}
	else
	{
		perror(str);
		if (fd >= 0)
			close(fd);
	}
	exit(1);
}