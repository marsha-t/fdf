#include "fdf.h"

int	ft_map_width(char *line)
{

}
t_map	*ft_parse_map(t_fdf *fdf, char *file)
{
	int		fd;
	t_map	*map;
	char	*line;
	
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error(ERR_OPEN, -1);
	map = malloc(sizeof(t_map));
	if (!map)
		ft_error(ERR_MALLOC_MAP, fd);
	line = get_next_line(fd);
	printf("line: %s\n", line);
	if (!line)
		ft_error(ERR_FILE_EMPTY, fd);
	map->height = 1;
	// map->width = ft_map_width(line);
	while (line)
	{
		line = get_next_line(fd);
		// ft_split(line, ' '); // need check that width is the same always 
		map->height++;
	}
	close(fd);
	return (map);
}

t_fdf	*ft_init(char *file)
{
	t_fdf	*fdf;
	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		ft_error("ERR_MALLOC_FDF", -1);
	fdf->map = ft_parse_map(fdf, file);
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		ft_error(ERR_MLX, -1);
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "fdf"); // need to change parameters
	if (!fdf->win)
		ft_error(ERR_WIN, -1);
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->img)
		ft_error(ERR_IMG, -1);
	fdf->data_addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel, &fdf->size_line, &fdf->endian);
	return (fdf);
}

// int	main(int argc, char **argv)
// {

// }

