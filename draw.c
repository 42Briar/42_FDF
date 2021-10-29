#include "fdf.h"

void	my_mlx_pixel_put(t_data *fdf, int x, int y, int color)
{
	char	*dst;

	if (x >= WIDTH || x < 0 || y >= HEIGHT || y < 0)
		return ;
	dst = fdf->addr + (y * fdf->line_length + x * (fdf->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static int	ft_select(bool val, int a, int b)
{
	if (val)
		return (a);
	return (b);
}

static void	define(t_var *delta, t_var *sign, t_var *cur, t_data *fdf)
{
	delta->x = abs(fdf->xy.x - cur->x);
	delta->y = abs(fdf->xy.y - cur->y);
	sign->x = ft_select(cur->x < fdf->xy.x, 1, -1);
	sign->y = ft_select(cur->y < fdf->xy.y, 1, -1);
}

void	drawline(t_var point1, t_var point2, t_data *fdf, t_var cxy)
{
	t_var	delta;
	t_var	sign;
	t_var	cur;
	int		error;

	cur = point1;
	fdf->xy = point2;
	define(&delta, &sign, &cur, fdf);
	error = 2 * (delta.y - delta.x);
	while (1)
	{
		my_mlx_pixel_put(fdf, cur.x, cur.y, fdf->map.colours[cxy.y][cxy.x]);
		if (cur.x == fdf->xy.x && cur.y == fdf->xy.y)
			break ;
		if (error >= 0)
		{
			cur.y += sign.y;
			error = error - 2 * delta.x;
		}
		if (error < 0)
		{
			cur.x += sign.x;
			error = error + 2 * delta.y;
		}
	}
}
