#include "fdf.h"

char	**readmap(int fd)
{
	char	*line[2];

	line[0] = (char *)1;
	line[1] = NULL;
	while (1)
	{
		line[0] = get_next_line(fd);
		if (!line[0])
			break ;
		line[1] = ft_strjoin(line[1], line[0]);
	}
	return (ft_split(line[1], '\n'));
}

int	store_colour(char *str, t_data *fdf, int i, int j)
{
	char	**arr;

	if (!ft_strchr(str, ','))
	{
		fdf->map.colours[i][j] = 0x00ffffff;
		return (ft_atoi(str));
	}	
	arr = ft_split(str, ',');
	fdf->map.colours[i][j] = ft_hextoint(arr[1] + 2);
	return (ft_atoi(arr[0]));
}

static void	define(char ***temp, t_data *fdf, int fd)
{
	*temp = readmap(fd);
	fdf->map.height = ft_arrlen(*temp);
	fdf->map.width = 0;
	fdf->map.coords = (int **)malloc(fdf->map.height * sizeof(int *));
	fdf->map.colours = (int **)malloc(fdf->map.height * sizeof(int *));
}

void	parsemap(int fd, t_data *fdf)
{
	char	**temp;
	char	**str;
	int		i;
	int		j;

	i = 0;
	define(&temp, fdf, fd);
	while (temp[i] != NULL)
	{
		j = 0;
		str = ft_split(temp[i], ' ');
		if (!fdf->map.width)
			fdf->map.width = ft_arrlen(str);
		fdf->map.coords[i] = (int *)malloc(fdf->map.width * sizeof(int));
		fdf->map.colours[i] = (int *)malloc(fdf->map.width * sizeof(int));
		while (str[j] != NULL)
		{
			fdf->map.coords[i][j] = store_colour(str[j], fdf, i, j);
			j++;
		}
		i++;
	}
	close(fd);
	drawmap(fdf);
}
