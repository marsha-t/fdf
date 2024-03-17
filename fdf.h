/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:14:12 by mateo             #+#    #+#             */
/*   Updated: 2024/03/15 11:54:44 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include "mlx/mlx.h"
#include "libft/libft.h"

# define ERR_ARGC		"Usage: ./fdf <filename>"
# define ERR_MALLOC_FDF	"Error allocating for fdf"
# define ERR_OPEN		"Error opening file"
# define ERR_MALLOC_MAP	"Error allocating for map"
# define ERR_MALLOC_BUF	"Error allocating for buffer"
# define ERR_MLX		"Error connecting to X server"
# define ERR_WIN 		"Error creating window"
# define ERR_IMG		"Error creating image"
# define ERR_CLOSE		"Error closing file"
# define ERR_READ		"Error reading file"
# define ERR_FILE		"File is not formatted correctly"
# define ERR_IRREGULAR	"Error in file: irregular line lengths"
# define ERR_MALLOC_ROW	"Error allocating for row"
# define ERR_COLOUR		"Error in file: colour not passed formatted properly"

# define WIDTH 1000
# define HEIGHT 2000

# define DEFAULT_MAP_COLOUR	"0xFFFFFF"

typedef struct 
{
	int	x;
	int	y;
	int	z;
	int	colour;
}				t_pt;

typedef	struct	s_fdf
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*data_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		map_fd;
	int		map_width;
	int		map_height;
	t_pt	**map;
}				t_fdf;

/*init.c*/
int	ft_nl_read(char *buffer);
int	ft_map_height(char *file);
int	ft_count_split(char **split);
t_pt	*ft_to_pt(char **split);
void	ft_parse_map(t_fdf *fdf, char *file);
t_fdf	*ft_init(char *file);

/*exit.c*/
void	ft_free_arrstr(char **split);
void	ft_free_fdf(t_fdf *fdf, int free_map); // to test!
void	ft_error(char *str);


/*ft_atoi_base.c*/
int	ft_base_ok(char *base);
int	ft_c_is_whitespace(char c);
int	ft_c_is_base(char c, char *base);
int	ft_atoi_base(char *str, char *base);

#endif