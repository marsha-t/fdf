/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:14:12 by mateo             #+#    #+#             */
/*   Updated: 2024/03/22 15:17:58 by mateo            ###   ########.fr       */
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
#include "keys.h"

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
# define ERR_EXT		"File is not .fdf"
# define ERR_MALLOC_NPT	"Error allocating for new point"
# define ERR_MALLOC_TPT "Error allocating for temp point"

# define WIDTH 1500
# define HEIGHT 1000
# define MENU 250

# define DEFAULT_COLOUR	0xFFFFFF

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
	int		bpp;
	int		size_line;
	int		endian;
	int		map_fd;
	int		map_height_fd;
	int		map_width;
	int		map_height;
	t_pt	**map;
	double	zoom;
	double	x_angle;
	double	y_angle;
	double	z_angle;
	int		x_min;
	int		x_max;
	int		y_min;
	int		y_max;
	int		x_shift;
	int		y_shift;
	int		project;
	int		space;
}				t_fdf;

/*utils.c*/
int		ft_abs(int x);
int		ft_min(int a, int b);
int		ft_max(int a, int b);

/*controls.c*/
void	ft_rotate(int key, t_fdf *fdf);
void	ft_move(int key, t_fdf *fdf);
void	ft_project(int key, t_fdf *fdf);
void	ft_zoom(int key, t_fdf *fdf);
int		ft_key(int key, void *param);

/*draw.c*/
void	ft_rotate_x(int *y, int *z, double x_angle);
void	ft_rotate_y(int *x, int *z, double y_angle);
void	ft_rotate_z(int *x, int *y, double z_angle);
t_pt	*ft_transform(t_pt point, t_fdf *fdf);
void	ft_put_pixel(t_pt *pt, t_fdf *fdf);
int		ft_gradient(t_pt *start, t_pt *end, t_pt *temp);
t_pt	*ft_line_setup(t_pt **start, t_pt **end, t_fdf *fdf);
void	ft_line(t_pt *start, t_pt *end, t_fdf *fdf);
int		ft_draw(t_fdf *fdf);

/*init.c*/
int	ft_nl_read(char *buffer);
void	ft_parse_map_error(t_fdf *fdf, char **split, char *error, int free_map);
int	ft_map_height(char *file, char **split, t_fdf *fdf);
int	ft_count_split(char **split);
int	ft_not_base(char *str, char *base);
int	ft_check_colour(char *str);
int	ft_map_colour(char **split, t_pt *row, int x, t_fdf *fdf);
int	ft_strisnum(char *str);
t_pt	*ft_fill_pt(t_fdf *fdf, char **split, int y);
int	ft_check_fdf(char *file);
void	ft_parse_line0(char *file, t_fdf *fdf);
void	ft_parse_lines(t_fdf *fdf);
void	ft_init_map(t_fdf *fdf);
void	ft_parse_map(t_fdf *fdf, char *file);
void	ft_init_transform(t_fdf *fdf);
t_fdf	*ft_init(char *file);

/*exit.c*/
void	ft_free_arrstr(char **split);
void	ft_free_fdf(t_fdf *fdf, int free_map);
void	ft_error(char *str);
int		ft_close(void *param);

/*ft_atoi_base.c*/
int	ft_base_ok(char *base);
int	ft_c_is_whitespace(char c);
int	ft_c_is_base(char c, char *base);
int	ft_atoi_base(char *str, char *base);

#endif