
#include "play.h"

t_player	*init_player(int x, int y, dir dir)
{
	t_player *res = malloc(sizeof(t_player));

	res->x = x;
	res->y = y;
	res->dir = dir;
	res->jumping = false;
	res->duration_jump = MAX_TIME_JUMP;
	res->jump_timestop = 0;
	return (res);
}

void 	init_data(t_mlx *data)
{
	data->ptr = mlx_init();
    data->window = mlx_new_window(data->ptr, WIDTH, HEIGHT, "battle snakes");
	data->image.img_ptr = mlx_new_image(data->ptr, WIDTH + 1, HEIGHT + 1);
	data->image.img_pixels_ptr = mlx_get_data_addr(data->image.img_ptr, &data->image.bits_per_pixel, &data->image.line_len, &data->image.endian);
	data->countdown = -3;
	data->first_p = init_player(START_POS, START_POS, DROITE);
	data->second_p = init_player(WIDTH - START_POS, HEIGHT - START_POS, GAUCHE);
}