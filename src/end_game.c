
#include "play.h"

int head_touches_color(t_player *player, t_img *img)
{
	int x = player->x;
	int y = player->y;
	int dx = x + SQUARE_SIZE;
	int dy = y + SQUARE_SIZE;
	int head1_x, head1_y, head2_x, head2_y;

	if (player->dir == DROITE)
	{
		head1_x = dx;
		head1_y = y;
		head2_x = dx;
		head2_y = dy;
	}
	else if (player->dir == HAUT)
	{
		head1_x = x;
		head1_y = y;
		head2_x = dx;
		head2_y = y;
	}
	else if (player->dir == GAUCHE)
	{
		head1_x = x;
		head1_y = y;
		head2_x = x;
		head2_y = dy;
	}
	else
	{
		head1_x = x;
		head1_y = dy;
		head2_x = dx;
		head2_y = dy;
	}
	if (head1_x >= WIDTH)
		head1_x -= WIDTH;
	if (head2_x >= WIDTH)
		head2_x -= WIDTH;
	if (head1_y >= HEIGHT)
		head1_y -= HEIGHT;
	if (head2_y >= HEIGHT)
		head2_y -= HEIGHT;
	if (get_pixel_color(img, head1_x, head1_y) != 0x000000
		|| get_pixel_color(img, head2_x, head2_y) != 0x000000)
		{
			return (1);
		}
	return (0);
}

void	check_death(t_mlx *data)
{
	int loser = 0;

	if (head_touches_color(data->first_p, &data->image) && data->first_p->jumping == false)
		loser = 1;
	if (head_touches_color(data->second_p, &data->image) && data->second_p->jumping == false)
	{
		if (loser == 1)
			loser = 3;//both players lose, works randomly
		else
			loser = 2;
	}
	if (loser == 1)
		data->countdown = -4;
	else if (loser == 2)
		data->countdown = -5;
	else if (loser == 3)
		data->countdown = -6;
}
