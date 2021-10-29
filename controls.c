#include "fdf.h"

void	rotate(int key, t_data *fdf)
{
	if (key == KEY_NP_4)
		fdf->camera.x_rot += 0.1;
	if (key == KEY_NP_6)
		fdf->camera.x_rot -= 0.1;
	if (key == KEY_NP_8)
		fdf->camera.y_rot += 0.1;
	if (key == KEY_NP_2)
		fdf->camera.y_rot -= 0.1;
	if (key == KEY_NP_7)
		fdf->camera.z_rot += 0.1;
	if (key == KEY_NP_9)
		fdf->camera.z_rot -= 0.1;
	drawmap(fdf);
}

void	camera(int keycode, t_data *fdf)
{
	if (keycode == KEY_NP_MIN)
		fdf->camera.zoom -= 1;
	if (keycode == KEY_NP_PLUS)
		fdf->camera.zoom += 1;
	if (keycode == KEY_A)
		fdf->camera.offsetx -= 10;
	if (keycode == KEY_D)
		fdf->camera.offsetx += 10;
	if (keycode == KEY_S)
		fdf->camera.offsety += 10;
	if (keycode == KEY_W)
		fdf->camera.offsety -= 10;
	drawmap(fdf);
}

void	flatten(int key, t_data *fdf)
{
	if (key == KEY_Q)
		fdf->camera.flatten += 1;
	if (key == KEY_E)
		fdf->camera.flatten -= 1;
	if (fdf->camera.flatten < 1)
		fdf->camera.flatten = 1;
	printf("%d\n", fdf->camera.flatten);
	drawmap(fdf);
}
