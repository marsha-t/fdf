
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>

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
	int		colour_change;
}				t_fdf;

/// libft
typedef struct s_gnl_list
{
	struct s_gnl_list	*next;
	struct s_gnl_list	*prev;
	char			*str;
	int				nl;
	int				eof;
}	t_gnl_list;

typedef struct s_gnl
{
	int fd;
	int free_static;
	int read_r;
	char *newline;
}	t_gnl;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);

int			ft_isdigit(int c);

int			ft_atoi(const char *str);

size_t		ft_strlen(const char *s);

char		*ft_strchr(const char *s, int c);

char		**ft_split(char const *s, char c);

void	*ft_gnl_lstclear(t_gnl_list **lst, int forward, t_gnl *meta);
t_gnl_list	*ft_lstaddnew(t_gnl_list **head, int blank);
t_gnl_list	*ft_lstsplit(t_gnl_list *last, char *newline);
int			ft_lststrlen(t_gnl_list *head, t_gnl_list *last);


char	*ft_lststrcat(int len, t_gnl_list **head, char *fullline, t_gnl *meta);
char	*ft_lststrcat_setup(t_gnl_list **head, t_gnl_list *last, t_gnl *meta);
t_gnl*	ft_gnl_meta(int fd, int free_static, t_gnl_list **head);
char		*get_next_line(int fd, int free_static);

/*ft_atoi_base.c*/
int	ft_base_ok(char *base)
{
	int	i;
	int	j;

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

/// exit

/* ft_free_arrstr frees an array of strings */
void	ft_free_arrstr(char **split)
{
	int	i;	

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
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

void	ft_error(char *str)
{
	if (errno == 0)
		ft_putendl_fd(str, 2);
	else
		perror(str);
	exit(1);
}


//// init

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

void	ft_parse_map_error(t_fdf *fdf, char **split, char *error, int free_map)
{
	printf("map_fd: %d, map_height_fd: %d, errno: %d\n", fdf->map_fd, fdf->map_height_fd, errno);
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
	get_next_line(fdf->map_fd, 1); // MT ADDED fixed to fdf-> map_fd
	if (split)
		ft_free_arrstr(split);
	ft_free_fdf(fdf, free_map);
	ft_error(error);
}

/* ft_map_height returns the height of the map */

int	ft_map_height(char *file, char **split, t_fdf *fdf)
{
	int		height;
	char	*buffer;
	int		r;

	fdf->map_height_fd = open(file, O_RDONLY);
	printf("open map_height_fd: %d\n", fdf->map_height_fd);
	if (fdf->map_height_fd == -1)
		ft_parse_map_error(fdf, split, ERR_OPEN, -2);
	height = 0;
	buffer = malloc(sizeof(char) * 5);
	if (!buffer)
		ft_parse_map_error(fdf, split, ERR_MALLOC_BUF, -2);
	buffer[4] = '\0';
	r = 1;
	while (r > 0)
	{
		r = read(fdf->map_height_fd, buffer, 4);
		if (r > 0)
			height += ft_nl_read(buffer);
		printf("r: %d, height: %d, buffer: %s\n", r, height, buffer);
	}
	free(buffer);
	if (r < -1)
		ft_parse_map_error(fdf, split, ERR_READ, -2);
	if (close(fdf->map_height_fd) == -1)
	{
		fdf->map_height_fd = -1;
		ft_parse_map_error(fdf, split, ERR_CLOSE, -2);
	}
	fdf->map_height_fd = -1; // MT ADDED

	return (height);
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

/* ft_not_base checks where str contains characters that are not in base */
int	ft_not_base(char *str, char *base) // check whether duplicates sth needed for atoi_base?
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
char *ft_struppr(char *str)
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

/* ft_map_colour parses the colour given in the map into a DECIMAL number
	- checks that the colour is provided correctly
	- parses a correctly provided colour and returns the DECIMAL number
	- returns a default colour if none is provided*/
int	ft_map_colour(char **split, t_pt *row, int x, t_fdf *fdf)
{
	char	*str;

	str = split[x];
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
		printf("x: %d, str: %s\n", x, str);
		printf("here 1\n");
		close(fdf->map_fd);
		ft_free_arrstr(split);
		ft_free_fdf(fdf, row->y - 1);
		free(row);
		ft_error(ERR_FILE);
	}
	return (DEFAULT_COLOUR);
}

/* ft_strisnum checks whether str is made up of digits 
	(until a null terminator or a comma) */
int	ft_strisnum(char *str)
{
	if (*str == '\0' || *str == '\n')
		return (0);
	while (*str && *str != ',' && *str != '\n')
	{
		if (ft_isdigit(*str) == 1 || *str == '-')
			str++;
		else
			return (0);
	}
	return (1);
}

/* ft_fill_pt parses array of str into array of t_pt 
	- frees split after parsing */
t_pt	*ft_fill_pt(t_fdf *fdf, char **split, int y)
{
	int		x;
	t_pt	*row;

	row = malloc(sizeof(t_pt) * fdf->map_width);
	if (!row)
		ft_parse_map_error(fdf, split, ERR_MALLOC_ROW, y - 1);
	x = 0;
	while (split[x])
	{
		row[x].x = x;
		row[x].y = y;
		if (ft_strisnum(split[x]) == 1)
			row[x].z = ft_atoi(split[x]);
		else
		{
			free(row);
			printf("here 2\n");
			ft_parse_map_error(fdf, split, ERR_FILE, y - 1);
		}
		row[x].colour = ft_map_colour(split, row, x, fdf);
		x++;
	}
	ft_free_arrstr(split);
	return (row);
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

/*	ft_parse_line0 parses the first line of fdf file
	- adds height and width into fdf */
void	ft_parse_line0(char *file, t_fdf *fdf)
{
	char	*line;
	char	**split;

	line = get_next_line(fdf->map_fd, 0);
	if (!line)
	{		
		printf("here 3\n");
		
		ft_parse_map_error(fdf, 0, ERR_FILE, -2);
		// close(fdf->map_fd);
		// fdf->map_fd = -1;
		// ft_free_fdf(fdf, -2);
		// ft_error(ERR_FILE);
	}
	split = ft_split(line, ' ');
	free(line);
	fdf->map_height = ft_map_height(file, split, fdf);
	fdf->map = malloc(sizeof(t_pt *) * fdf->map_height);
	if (!fdf->map)
		ft_parse_map_error(fdf, split, ERR_MALLOC_MAP, -2);
	fdf->map_width = ft_count_split(split);
	fdf->map[0] = ft_fill_pt(fdf, split, 0);
}

/*	ft_parse_lines parses the rest of fdf file*/
void	ft_parse_lines(t_fdf *fdf)
{
	int		y;
	char	*line;
	char	**split;

	y = 1;
	while (y < fdf->map_height)
	{
		line = get_next_line(fdf->map_fd, 0);
		if (!line)
		{
			printf("here 4\n");

			ft_parse_map_error(fdf, 0, ERR_FILE, y - 1);
		}
		split = ft_split(line, ' ');
		free(line);
		if (ft_count_split(split) == fdf->map_width)
		{
			fdf->map[y] = ft_fill_pt(fdf, split, y);
			y++;
		}
		else
		{
			printf("here 5\n");
			
			ft_parse_map_error(fdf, split, ERR_FILE, y - 1);
		}
	}
}

void	ft_init_map(t_fdf *fdf)
{
	fdf->map_fd = -1;
	fdf->map_height_fd = -1;
	fdf->map_width = -1;
	fdf->map_height = -1;
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
	printf("open map_fd: %d\n", fdf->map_fd);
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

////////////// MAIN.C 
int	main(int argc, char **argv)
{
	t_fdf	*fdf;
	if (argc == 2)
	{
		fdf = ft_init(argv[1]);
		printf("fdf: map_fd: %d, map_width: %d, map_height: %d\n", fdf->map_fd, fdf->map_width, fdf->map_height);
		// printf("map: (0,0): (%d, %d, %d, %d)\n", fdf->map[0][0].x, fdf->map[0][0].y, fdf->map[0][0].z, fdf->map[0][0].colour);
		// printf("map: (1,0) (%d, %d, %d, %d)\n", fdf->map[0][1].x, fdf->map[0][1].y, fdf->map[0][1].z, fdf->map[0][1].colour);
		// printf("map: (0,1): (%d, %d, %d, %d)\n", fdf->map[1][0].x, fdf->map[1][0].y, fdf->map[1][0].z, fdf->map[1][0].colour);
		// printf("map: (1,1) (%d, %d, %d, %d)\n", fdf->map[1][1].x, fdf->map[1][1].y, fdf->map[1][1].z, fdf->map[1][1].colour);
		ft_free_fdf(fdf, fdf->map_height - 1); // added -1
	}
	else
		ft_error(ERR_ARGC);
	return (0);	
}
