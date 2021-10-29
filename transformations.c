#include "fdf.h"

void	isometric(int *x, int *y, int z)
{
	int	previous_x;
	int	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
}

void	rot_x(int *y, int *z, double x_rot)
{
	int	previous_y;
	int	prev_z;

	previous_y = *y;
	prev_z = *z;
	*y = previous_y * cos(x_rot) + prev_z * sin(x_rot);
	*z = -previous_y * sin(x_rot) + prev_z * cos(x_rot);
}

void	rot_y(int *x, int *z, double y_rot)
{
	int	prev_x;
	int	prev_z;

	prev_x = *x;
	prev_z = *z;
	*x = prev_x * cos(y_rot) + prev_z * sin(y_rot);
	*z = -prev_x * sin(y_rot) + prev_z * cos(y_rot);
}

void	rot_z(int *x, int *y, double z_rot)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = prev_x * cos(z_rot) - prev_y * sin(z_rot);
	*y = prev_x * sin(z_rot) + prev_y * cos(z_rot);
}
