#ifndef FDF_H
# define FDF_H

# include "../mlx/mlx.h"
# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
# include "keycodes.h"
# include "colours.h"

# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h> 

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_paint {
	int	x;
	int	y;
	int	mode;

}	t_paint;

typedef struct s_map {
	int				**coords;
	int				**colours;
	int				width;
	int				height;

}	t_map;

typedef struct s_camera {
	int		zoom;
	int		offsetx;
	int		offsety;
	double	z_rot;
	double	x_rot;
	double	y_rot;

}	t_cam;

typedef struct s_var {
	int	x;
	int	y;
}	t_var;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	void	*mlx_win;
	t_paint	paint;
	t_map	map;
	t_var	xy;
	t_cam	camera;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	drawline(t_var point1, t_var point2, t_data *fdf, t_var colourxy);
void	parsemap(int fd, t_data *fdf);
void	drawmap(t_data *fdf);
void	isometric(int *x, int *y, int z);
void	camera(int keycode, t_data *fdf);
void	rotate(int keycode, t_data *fdf);
void	rot_x(int *y, int *z, double x_rot);
void	rot_y(int *x, int *z, double y_rot);
void	rot_z(int *x, int *y, double z_rot);

#endif