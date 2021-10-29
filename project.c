#include "fdf.h"

t_coord	project(int x, int y, t_data *fdf)
{
	t_coord	iso;

	iso.x = x * fdf->camera.zoom;
	iso.y = y * fdf->camera.zoom;
	iso.z = fdf->map.coords[y][x] * (fdf->camera.zoom / fdf->camera.flatten);
	rot_x(&iso.y, &iso.z, fdf->camera.x_rot);
	rot_y(&iso.x, &iso.z, fdf->camera.y_rot);
	rot_z(&iso.x, &iso.y, fdf->camera.z_rot);
	isometric(&iso.x, &iso.y, iso.z);
	iso.x += (WIDTH / 2) + fdf->camera.offsetx;
	iso.y += (HEIGHT / 2) + fdf->camera.offsety;
	return (iso);
}

static void	draw_background(t_data *fdf)
{
	int	*image;
	int	i;

	ft_bzero(fdf->addr, WIDTH * HEIGHT * (fdf->bits_per_pixel / 8));
	image = (int *)(fdf->addr);
	i = 0;
	while (i < HEIGHT * WIDTH)
	{
		image[i] = 0x0;
		i++;
	}
}

void	drawmap(t_data *fdf)
{
	int		x;
	int		y;
	t_var	colourxy;

	draw_background(fdf);
	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			colourxy.x = x;
			colourxy.y = y;
			if (y != fdf->map.height - 1)
				drawline(project(x, y, fdf), project(x, y + 1, fdf), \
				 fdf, colourxy);
			if (x != fdf->map.width - 1)
				drawline(project(x, y, fdf), project(x + 1, y, fdf), \
				fdf, colourxy);
			x++;
		}
		y++;
	}
	mlx_clear_window(fdf->mlx, fdf->mlx_win);
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->img, 0, 0);
}
