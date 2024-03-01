#include "../../include/cub3d.h"

void	w_rgb_to_map(t_data *data)
{
	data->floor_color = (data->map.f[0] << 16) + (data->map.f[1] << 8) + data->map.f[2];
	data->ceiling_color = (data->map.c[0] << 16) + (data->map.c[1] << 8) + data->map.c[2];
	// printf("floor_color = %d\n", data->floor_color);
	// printf("ceiling_color = %d\n", data->ceiling_color);
}


void	wall_image(t_data *data)
{
	data->img_data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img_data->addr = mlx_get_data_addr(data->img_data->img,
			&data->img_data->bpp,
			&data->img_data->line_length, &data->img_data->endian);
	data->imgs[0].img = data->ea_img;
	data->imgs[1].img = data->no_img;
	data->imgs[2].img = data->so_img;
	data->imgs[3].img = data->we_img;
	data->imgs[0].addr = mlx_get_data_addr(data->imgs[0].img, \
		&data->imgs[0].bpp, &data->imgs[0].line_length, &data->imgs[0].endian);
	data->imgs[1].addr = mlx_get_data_addr(data->imgs[1].img, \
		&data->imgs[1].bpp, &data->imgs[1].line_length, &data->imgs[1].endian);
	data->imgs[2].addr = mlx_get_data_addr(data->imgs[2].img, \
		&data->imgs[2].bpp, &data->imgs[2].line_length, &data->imgs[2].endian);
	data->imgs[3].addr = mlx_get_data_addr(data->imgs[3].img, \
		&data->imgs[3].bpp, &data->imgs[3].line_length, &data->imgs[3].endian);

}
