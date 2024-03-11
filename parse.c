#include "fdf.h"

void	ft_error(char *str)
{
	if (errno == 0)
		ft_putendl_fd(str, 2);
	else
		perror(str);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		
	}
	else
		ft_error("Usage: ./fdf <filename>");
}