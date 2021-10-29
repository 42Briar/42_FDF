#include "fdf.h"

int	mouse_hook(int button, int x, int y, t_data *fdf)
{
	if (button == 2)
	{
		mlx_clear_window(fdf->mlx, fdf->mlx_win);
	}
	return (0);
}

int	key_hook(int keycode, t_data *fdf)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(fdf->mlx, fdf->mlx_win);
		exit(0);
	}
	if (keycode == KEY_NP_MIN || keycode == KEY_NP_PLUS || \
	keycode == KEY_A || keycode == KEY_D || keycode == KEY_S || \
	keycode == KEY_W)
		camera(keycode, fdf);
	if (keycode == KEY_NP_1 || keycode == KEY_NP_2 || keycode == KEY_NP_3 || \
	keycode == KEY_NP_4 || keycode == KEY_NP_6 || keycode == KEY_NP_7 || \
	keycode == KEY_NP_8 || keycode == KEY_NP_9)
		rotate(keycode, fdf);
	if (keycode == KEY_Q || keycode == KEY_E)
		flatten(keycode, fdf);
	return (0);
}

static t_data	*init(t_data *fdf)
{
	fdf = (t_data *)ft_memalloc(sizeof(t_data));
	fdf->mlx = mlx_init();
	fdf->mlx_win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FDF");
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->addr = mlx_get_data_addr(fdf->img, &(fdf->bits_per_pixel), \
	&(fdf->line_length), &(fdf->endian));
	fdf->camera.zoom = 10;
	fdf->camera.offsetx = -100;
	fdf->camera.offsety = -100;
	fdf->camera.x_rot = 0;
	fdf->camera.y_rot = 0;
	fdf->camera.z_rot = 0;
	fdf->camera.flatten = 1;
	return (fdf);
}

int	main(int argc, char *argv[])
{
	t_data	*fdf;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	fdf = init(fdf);
	parsemap(fd, fdf);
	mlx_mouse_hook(fdf->mlx_win, mouse_hook, fdf);
	mlx_key_hook(fdf->mlx_win, key_hook, fdf);
	mlx_loop(fdf->mlx);
}
