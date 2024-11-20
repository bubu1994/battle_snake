
#include "play.h"

void	player_move(t_player *play)
{
	if (play->dir == DROITE)
		play->x += 1;
	else if (play->dir == HAUT)
		play->y -= 1;
	else if (play->dir == GAUCHE)
		play->x -= 1;
	else if (play->dir == BAS)
		play->y += 1;
	
	if (play->x >= WIDTH)
		play->x -= WIDTH;
	else if (play->x < 0)
		play->x += WIDTH;
	if (play->y >= HEIGHT)
		play->y -= HEIGHT;
	else if (play->y < 0)
		play->y += HEIGHT;
}

int	moving_players(t_mlx *data)
{
	if (get_current_time_in_ms() > data->last_time + MS_PER_PIXEL)
	{
		player_move(data->first_p);
		player_move(data->second_p);
		data->last_time = get_current_time_in_ms();
		check_death(data);
		return (1);
	}
	return (0);
}

void jump_countdown(t_mlx *data)
{
	if (data->first_p->jumping)
		data->first_p->duration_jump -= MS_PER_PIXEL;
	if (data->second_p->jumping)
		data->second_p->duration_jump -= MS_PER_PIXEL;
	if (data->first_p->duration_jump < 0)
		data->first_p->jumping = false;
	if (data->second_p->duration_jump < 0)
		data->second_p->jumping = false;
}

void display_end_play(t_mlx *data)
{
	char win_msg[10];

	if (data->countdown == -5)
		strcpy(win_msg, "Blue wins");
	else if (data->countdown == -4)
		strcpy(win_msg, "Red wins");
	else
		strcpy(win_msg, "Tie");
	put_rectangle(&data->image, 200, 50, (WIDTH / 2) - 100, (HEIGHT / 2) - 25, 0xA0A0A0);
	mlx_put_image_to_window(data->ptr, data->window, data->image.img_ptr, 0, 0);
	mlx_string_put(data->ptr, data->window, WIDTH / 2 - 30, HEIGHT / 2 - 10, 0xFFFFFF, win_msg);
	mlx_string_put(data->ptr, data->window, WIDTH / 2 - 80, HEIGHT / 2 + 5, 0xFFFFFF, "Press \'G\' to start a game");
}

int render_loop(t_mlx *data)
{
	long	current_time = get_current_time_in_ms();

	//countdown 3...2...1
	if (data->countdown >= 0 && current_time - data->last_time >= 1000)
	{
		mlx_clear_window(data->ptr, data->window);
		data->first_p->duration_jump = MAX_TIME_JUMP;
		data->second_p->duration_jump = MAX_TIME_JUMP;
		put_square(&data->image, data->first_p->x, data->first_p->y, COLOR_1);
		put_square(&data->image, data->second_p->x, data->second_p->y, COLOR_2);
		mlx_put_image_to_window(data->ptr, data->window, data->image.img_ptr, 0, 0);
		char str[2] = {'0' + data->countdown, '\0'};
		mlx_string_put(data->ptr, data->window, WIDTH / 2, HEIGHT / 2, 0xFFFFFF, str);
		data->countdown--;
		data->last_time = get_current_time_in_ms();
	}
	else if (data->countdown == -1)
	{
		if (!moving_players(data))
			return (0);
		//loops here every {MS_PER_PIXEL}
		jump_countdown(data);
		if (data->first_p->jumping == false)
			put_square(&data->image, data->first_p->x, data->first_p->y, COLOR_1);
		if (data->second_p->jumping == false)
			put_square(&data->image, data->second_p->x, data->second_p->y, COLOR_2);
		mlx_put_image_to_window(data->ptr, data->window, data->image.img_ptr, 0, 0);
		if (data->countdown <= -4 && data->countdown >= -6)
			display_end_play(data);
	}
	return (0);
}
