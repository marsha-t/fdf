

#ifndef FDF_H

# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "libft.h"

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
# define ERR_LIMITS		"File goes beyond INT_MAX or INT_MIN"
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

typedef struct s_pt
{
	int	x;
	int	y;
	int	z;
	int	colour;
}				t_pt;

typedef struct s_fdf
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
	char	**split;
	t_pt	**map;
	double	zoom;
	double	x_angle;
	double	y_angle;
	double	z_angle;
	int		x_shift;
	int		y_shift;
	int		project;
	int		space;
	int		colour_change;
	int		x_min;
	int		x_max;
	int		y_min;
	int		y_max;
	int		new_width;
	int		new_height;
	int		new_zoom;
}				t_fdf;

typedef struct s_dim
{
	int		min_sum_x;
	int		max_sum_x;
	int		min_sum_y;
	int		max_sum_y;
	t_pt	*x_min;
	t_pt	*x_max;
	t_pt	*y_min;
	t_pt	*y_max;
}	t_dim;

/* utils.c: Basic utility functions*/
int		ft_abs(int x);
double	ft_min(double a, double b);
int		key_num(int key);

/*controls.c: Responses to keypress*/
void	ft_rotate(int key, t_fdf *fdf);
void	ft_move(int key, t_fdf *fdf);
void	ft_project(int key, t_fdf *fdf);
void	ft_zoom(int key, t_fdf *fdf);
int		ft_key(int key, void *param);

/* rotations.c: Rotation of axes and isometric projection*/
void	ft_rotate_x(int *y, int *z, double x_angle);
void	ft_rotate_y(int *x, int *z, double y_angle);
void	ft_rotate_z(int *x, int *y, double z_angle);
void	ft_iso(t_pt *pt);

/*colour.c: Calculation of gradient and change in colours if C is pressed */
int		ft_change_colour(int colour);
int		ft_gradient(t_pt *start, t_pt *end, t_pt *temp);

/*dimensions.c: Calculation of dimensions of projected map */
void	ft_update_new(t_fdf *fdf, t_dim *points);
t_dim	*ft_init_points(void);
void	ft_find_minmax(int x, int y, t_fdf *fdf, t_dim *points);
void	ft_update_dimensions(t_fdf *fdf);

/*draw.c: Transform coordinates and place them into window */
void	ft_transform_main(t_pt *new_pt, t_pt *point, t_fdf *fdf);
t_pt	*ft_transform(t_pt *point, t_fdf *fdf);
void	ft_put_pixel(t_pt *pt, t_fdf *fdf);
void	ft_menu(t_fdf *fdf);
int		ft_draw(t_fdf *fdf);

/*line.c: Draw line using Bresenham's line algorithm */
t_pt	*ft_line_setup(t_pt **start, t_pt **end, t_fdf *fdf);
void	ft_line_gentle(t_pt *start, t_pt *end, t_pt *temp, t_fdf *fdf);
void	ft_line_steep(t_pt *start, t_pt *end, t_pt *temp, t_fdf *fdf);
void	ft_line(t_pt *start, t_pt *end, t_fdf *fdf);

/*parse_checks.c: Checks for errors in map */
int		ft_not_base(char *str, char *base);
int		ft_check_colour(char *str);
int		ft_strisnum(char *str);
int		ft_check_fdf(char *file);

/*parse_utils.c: Utility functions for parsing of map */
int		ft_nl_read(char *buffer);
int		ft_count_split(char **split);
char	*ft_struppr(char *str);
void	ft_parse_map_error(t_fdf *fdf, char *error, int free_map);
int		ft_first_digit(int x);

/*parse_components.c: Parses the components contained within fdf file */
int		ft_map_height_count(t_fdf *fdf);
int		ft_map_height(char *file, t_fdf *fdf);
int		ft_map_colour(t_pt *row, int x, t_fdf *fdf);

/*parse_lines.c: Parsing of lines within fdf file*/
void	ft_parse_line0(char *file, t_fdf *fdf);
int		ft_get_z(t_fdf *fdf, int x, t_pt *row, int y);
t_pt	*ft_fill_pt(t_fdf *fdf, int y);
void	ft_parse_lines(t_fdf *fdf);

/*init.c: Initialisation of structures*/
void	ft_init_map(t_fdf *fdf);
void	ft_parse_map(t_fdf *fdf, char *file);
void	ft_init_transform(t_fdf *fdf);
t_fdf	*ft_init(char *file);

/*exit.c: Exit/Error functions*/
void	ft_free_arrstr(t_fdf *fdf);
void	ft_free_fdf(t_fdf *fdf, int free_map);
void	ft_error(char *str);
int		ft_close(void *param);

/*ft_atoi_base.c: Conversion from array to int from different base */
int		ft_base_ok(char *base);
int		ft_c_is_whitespace(char c);
int		ft_c_is_base(char c, char *base);
int		ft_atoi_base(char *str, char *base);

#endif


#ifndef KEYS_H

# define KEYS_H

# define KEY_ESC 53
# define KEY_Q 12
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_Z 6
# define KEY_X 7
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_LEFT 123

# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_THREE 20
# define KEY_FOUR 21
# define KEY_FIVE 23
# define KEY_SIX 22
# define KEY_SEVEN 26

# define KEY_NP_ONE 83
# define KEY_NP_TWO 84
# define KEY_NP_THREE 85
# define KEY_NP_FOUR 86
# define KEY_NP_FIVE 87
# define KEY_NP_SIX 88
# define KEY_NP_SEVEN 89

# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_NP_PLUS 69
# define KEY_NP_MINUS 78

# define KEY_SPACE 49 
# define KEY_C 8

#endif
/// exit.c 

/* ft_free_arrstr frees an array of strings */
void	ft_free_arrstr(t_fdf *fdf)
{
	int	i;	

	i = 0;
	while (fdf->split[i])
	{
		free(fdf->split[i]);
		fdf->split[i] = 0;
		i++;
	}
	free(fdf->split);
	fdf->split = 0;
}

/* ft_free_fdf frees fdf as well as fdf->map
	- free_map = -2: only free fdf
	- free_map = -1: free fdf and fdf->map
	- free_map > -1: free fdf, fdf->map and free_map rows of fdf->map 
		(including free_map = 0 i.e., the first row)*/
void	ft_free_fdf(t_fdf *fdf, int free_map)
{
	int	h;

	if (free_map >= 0)
	{
		h = 0;
		while (h <= free_map)
		{
			free(fdf->map[h]);
			h++;
		}
	}
	if (free_map >= -1)
		free(fdf->map);
	free(fdf);
}

/*	ft_error prints error message in conjunction with perror if necessary */
void	ft_error(char *str)
{
	if (errno == 0)
		ft_putendl_fd(str, 2);
	else
		perror(str);
	exit(1);
}

/*	ft_close cleans up resources (window, image, allocated memory)*/
int	ft_close(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	// mlx_destroy_image(fdf->mlx, fdf->img);
	// mlx_destroy_window(fdf->mlx, fdf->win);
	ft_free_fdf(fdf, fdf->map_height - 1);
	exit(0);
}

/// utils.c 

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

/// ft_atoi_base

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

/// parse_utils.c
/* ft_nl_read returns the number of new line characters contained in buffer */
int	ft_nl_read(char *buffer)
{
	int	count;

	count = 0;
	while (*buffer)
	{
		if (*buffer == '\n')
			count++;
		buffer++;
	}
	return (count);
}

/* ft_count_split returns the number of strings in an array of strings 
	(assuming that there is a null pointer at the end of the array)*/
int	ft_count_split(char **split)
{
	int	count;

	count = 0;
	while (*split)
	{
		count++;
		split++;
	}
	return (count);
}

/*	ft_strupper converts string to uppercase*/
char	*ft_struppr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
		i++;
	}
	return (str);
}

/*	ft_parse_map_error closes fd(s) and frees resources*/
void	ft_parse_map_error(t_fdf *fdf, char *error, int free_map)
{
	if (fdf->map_fd >= 0)
	{
		close(fdf->map_fd);
		fdf->map_fd = -1;
	}
	if (fdf->map_height_fd >= 0)
	{
		close(fdf->map_height_fd);
		fdf->map_height_fd = -1;
	}
	get_next_line(fdf->map_fd, 1);
	if (fdf->split)
		ft_free_arrstr(fdf);
	ft_free_fdf(fdf, free_map);
	ft_error(error);
}

/*	ft_first_digit returns the first digit of int */
int	ft_first_digit(int x)
{
	int	d;

	d = x;
	while (x / 10 > 0)
	{
		x /= 10;
		d = x;
	}
	return (d);
}

///// parse_checks.c
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

////// parse_components.c
/*	ft_map_height_count reads from reopened file and 
	counts number of newlines */
int	ft_map_height_count(t_fdf *fdf)
{
	int		height;
	char	*buffer;
	int		r;

	height = 0;
	buffer = malloc(sizeof(char) * 5);
	if (!buffer)
		ft_parse_map_error(fdf, ERR_MALLOC_BUF, -2);
	buffer[4] = '\0';
	r = 1;
	while (r > 0)
	{
		r = read(fdf->map_height_fd, buffer, 4);
		height += ft_nl_read(buffer);
		ft_bzero(buffer, 5);
	}
	free(buffer);
	if (r < -1)
		ft_parse_map_error(fdf, ERR_READ, -2);
	return (height);
}

/* ft_map_height returns the height of the map */
int	ft_map_height(char *file, t_fdf *fdf)
{
	int		height;

	fdf->map_height_fd = open(file, O_RDONLY);
	if (fdf->map_height_fd == -1)
		ft_parse_map_error(fdf, ERR_OPEN, -2);
	height = ft_map_height_count(fdf);
	if (close(fdf->map_height_fd) == -1)
	{
		fdf->map_height_fd = -1;
		ft_parse_map_error(fdf, ERR_CLOSE, -2);
	}
	fdf->map_height_fd = -1;
	return (height);
}

/* ft_map_colour parses the colour given in the map into a DECIMAL number
	- checks that the colour is provided correctly
	- parses a correctly provided colour and returns the DECIMAL number
	- returns a default colour if none is provided*/
int	ft_map_colour(t_pt *row, int x, t_fdf *fdf)
{
	char	*str;

	str = fdf->split[x];
	while (*str && *str != ',')
		str++;
	if (*str == ',' && ft_check_colour(str + 1) == 1)
	{
		str += 3;
		str = ft_struppr(str);
		return (ft_atoi_base(str, "0123456789ABCDEF"));
	}
	else if (*str == ',' && ft_check_colour(str + 1) == 0)
	{
		close(fdf->map_fd);
		ft_free_arrstr(fdf);
		ft_free_fdf(fdf, row->y - 1);
		free(row);
		ft_error(ERR_FILE);
	}
	return (DEFAULT_COLOUR);
}

////// parse_lines.c
/*	ft_parse_line0 parses the first line of fdf file
	- adds height and width into fdf */
void	ft_parse_line0(char *file, t_fdf *fdf)
{
	char	*line;

	line = get_next_line(fdf->map_fd, 0);
	if (!line)
		ft_parse_map_error(fdf, ERR_FILE, -2);
	fdf->split = ft_split(line, ' ', '\n');
	free(line);
	fdf->map_height = ft_map_height(file, fdf);
	fdf->map = malloc(sizeof(t_pt *) * fdf->map_height);
	if (!fdf->map)
		ft_parse_map_error(fdf, ERR_MALLOC_MAP, -2);
	fdf->map_width = ft_count_split(fdf->split);
	if (fdf->map_width == 0 || fdf->map_height == 0)
		ft_parse_map_error(fdf, ERR_FILE, -1);
	fdf->map[0] = ft_fill_pt(fdf, 0);
}

/*	ft_get_z extracts z 
	and checks that it is not beyond INT_MAX and INT_MIN*/
int	ft_get_z(t_fdf *fdf, int x, t_pt *row, int y)
{
	int	z;

	z = ft_atoi(fdf->split[x]);
	if ((z == 0 && fdf->split[x][0] != '0') || \
		(z == -1 && fdf->split[x][0] != '-') || \
		(z > 0 && ft_first_digit(z) != fdf->split[x][0]) || \
		(z < 0 && ft_first_digit(-z) != fdf->split[x][1]))
	{
		free(row);
		ft_parse_map_error(fdf, ERR_LIMITS, y - 1);
	}
	return (z);
}

/* ft_fill_pt parses array of str into array of t_pt 
	- frees split after parsing */
t_pt	*ft_fill_pt(t_fdf *fdf, int y)
{
	int		x;
	t_pt	*row;

	row = malloc(sizeof(t_pt) * fdf->map_width);
	if (!row)
		ft_parse_map_error(fdf, ERR_MALLOC_ROW, y - 1);
	x = 0;
	while (fdf->split[x])
	{
		row[x].x = x;
		row[x].y = y;
		if (ft_strisnum(fdf->split[x]) == 1)
			row[x].z = ft_get_z(fdf, x, row, y);
		else
		{
			free(row);
			ft_parse_map_error(fdf, ERR_FILE, y - 1);
		}
		row[x].colour = ft_map_colour(row, x, fdf);
		x++;
	}
	ft_free_arrstr(fdf);
	return (row);
}

/*	ft_parse_lines parses the rest of fdf file*/
void	ft_parse_lines(t_fdf *fdf)
{
	int		y;
	char	*line;

	y = 1;
	while (y < fdf->map_height)
	{
		line = get_next_line(fdf->map_fd, 0);
		if (!line)
			ft_parse_map_error(fdf, ERR_FILE, y - 1);
		fdf->split = ft_split(line, ' ', '\n');
		free(line);
		if (ft_count_split(fdf->split) == fdf->map_width)
		{
			fdf->map[y] = ft_fill_pt(fdf, y);
			y++;
		}
		else
			ft_parse_map_error(fdf, ERR_FILE, y - 1);
	}
}
////////// init.c
/*	ft_init_map initialises map values */
void	ft_init_map(t_fdf *fdf)
{
	fdf->map_fd = -1;
	fdf->map_height_fd = -1;
	fdf->map_width = -1;
	fdf->map_height = -1;
	fdf->split = 0;
}

/*	ft_parse_map parses the fdf file into array of pt*/
void	ft_parse_map(t_fdf *fdf, char *file)
{
	if (ft_check_fdf(file) == 0)
	{
		ft_free_fdf(fdf, -2);
		ft_error(ERR_EXT);
	}
	ft_init_map(fdf);
	fdf->map_fd = open(file, O_RDONLY);
	if (fdf->map_fd == -1)
	{
		ft_free_fdf(fdf, -2);
		ft_error(ERR_OPEN);
	}
	ft_parse_line0(file, fdf);
	ft_parse_lines(fdf);
	if (close(fdf->map_fd) == -1)
	{
		ft_free_fdf(fdf, fdf->map_height - 1);
		ft_error(ERR_CLOSE);
	}
}

/*	ft_init sets up the fdf struct*/
t_fdf	*ft_init(char *file)
{
	t_fdf	*fdf;

	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		ft_error(ERR_MALLOC_FDF);
	ft_parse_map(fdf, file);
	return (fdf);
}

////////// main.c
int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc == 2)
	{
		fdf = ft_init(argv[1]);
	}
	else
		ft_error(ERR_ARGC);
	return (0);
}
