#include "fdf.h"

static void	readmap(int fd, char ***temp)
{
	char	buf[1000001];
	char	*map;
	int		bread;

	bread = 1;
	map = NULL;
	while (bread > 0)
	{
		bread = read(fd, buf, 1000000);
		buf[bread] = 0;
		if (bread == 0)
			break ;
		map = ft_strjoin(map, buf);
	}
	*temp = ft_split(map, '\n');
	free(map);
}

static void	store_colour(char *str, t_data *fdf, int i, int j)
{
	char	**arr;

	if (!ft_strchr(str, ','))
	{
		fdf->map.colours[i][j] = WHITE;
		fdf->map.coords[i][j] = ft_atoi(str);
	}
	else
	{
		arr = ft_split(str, ',');
		fdf->map.colours[i][j] = ft_hextoint(arr[1] + 2);
		fdf->map.coords[i][j] = ft_atoi(arr[0]);
		free(arr[0]);
		free(arr[1]);
		free(arr);
	}
}

static void	define(char ***temp, t_data *fdf, int fd)
{
	readmap(fd, temp);
	fdf->map.height = ft_arrlen(*temp);
	fdf->map.width = 0;
	fdf->map.coords = (int **)malloc(fdf->map.height * sizeof(int *));
	if (!fdf->map.coords)
		terminate(NULL);
	fdf->map.colours = (int **)malloc(fdf->map.height * sizeof(int *));
	if (!fdf->map.colours)
		terminate(NULL);
}

static void	alloc(t_data *fdf, int i)
{
	fdf->map.coords[i] = (int *)malloc(fdf->map.width * sizeof(int));
	if (!fdf->map.coords[i])
		terminate(NULL);
	fdf->map.colours[i] = (int *)malloc(fdf->map.width * sizeof(int));
	if (!fdf->map.colours[i])
		terminate(NULL);
}

void	parsemap(int fd, t_data *fdf)
{
	char	**temp;
	char	**str;
	int		i;
	int		j;

	i = -1;
	define(&temp, fdf, fd);
	while (temp[++i] != NULL)
	{
		j = -1;
		str = ft_split(temp[i], ' ');
		free(temp[i]);
		if (!fdf->map.width)
			fdf->map.width = ft_arrlen(str);
		alloc(fdf, i);
		while (str[++j] != NULL)
		{
			store_colour(str[j], fdf, i, j);
			free(str[j]);
		}
		free(str);
	}
	free(temp);
	drawmap(fdf);
}
