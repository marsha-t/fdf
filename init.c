#include "fdf.h"

t_map	*ft_parse_map(t_fdf *fdf, char *file)
{
	int		fd;
	t_map	*map;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error(ERR_OPEN);
	map = malloc(sizeof(t_map));
	if (!map)
		ft_error(ERR_MALLOC_MAP);
	
}

t_fdf	*ft_init(char *file)
{
	t_fdf	*fdf;
	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		ft_error("ERR_MALLOC_FDF");
	fdf->map = ft_parse_map(fdf, file);
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		ft_error(ERR_MLX);
	fdf->win = mlx_new_window(fdf->mlx, 50, 50, "My Window"); // need to change parameters
	if (!fdf->win)
		ft_error(ERR_WIN);
}
// int	main(int argc, char **argv)
// {

// }

