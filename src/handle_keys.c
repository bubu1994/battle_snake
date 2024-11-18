
#include "play.h"

void direction_change(int key, t_mlx *data)
{
	if (key == A)
	{
		if (data->first_p->dir == 3)
			data->first_p->dir = 0;
		else
			data->first_p->dir += 1;
	}
	else if (key == D)
	{
		if (data->first_p->dir == 0)
			data->first_p->dir = 3;
		else
			data->first_p->dir -= 1;
	}
	if (key == LEFT_A)
	{
		if (data->second_p->dir == 3)
			data->second_p->dir = 0;
		else
			data->second_p->dir += 1;
	}
	else if (key == RIGHT_A)
	{
		if (data->second_p->dir == 0)
			data->second_p->dir = 3;
		else
			data->second_p->dir -= 1;
	}
}

void start_game(t_mlx *data)
{
	clear_image(&data->image);
	data->first_p->x = START_POS;
	data->first_p->y = START_POS;
	data->first_p->dir = DROITE;
	data->second_p->x = WIDTH - START_POS;
	data->second_p->y = HEIGHT - START_POS;
	data->second_p->dir = GAUCHE;
	data->countdown = 3;
	data->last_time = time(NULL);
}

void jumping(int key, t_mlx *data)
{
	if (key == W && data->first_p->duration_jump > 0)
		data->first_p->jumping = true;
	if (key == UP_A && data->second_p->duration_jump > 0)
		data->second_p->jumping = true;
}

int the_game(int key, t_mlx *data)
{
	if (key == G)
		start_game(data);
	direction_change(key, data);
	jumping(key, data);
	if (key == ESC_K)
	{
		free(data->first_p);
		free(data->second_p);
		mlx_destroy_image(data->ptr, data->image.img_ptr);
		mlx_destroy_window(data->ptr, data->window);
		exit(0);
	}
	return (0);
}

int key_release(int key, t_mlx *data)
{
	if (key == W)
		data->first_p->jumping = false;
	if (key == UP_A)
		data->second_p->jumping = false;
	return (0);
}