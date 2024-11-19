#ifndef PLAY_H
#define PLAY_H

# include <math.h>
# include <time.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <stdio.h>

# define WIDTH 1200
# define HEIGHT 800
# define SQUARE_SIZE 10
# define COLOR_1 0xAAFFFF
# define COLOR_2 0xFF2424
# define START_POS 200
# define MS_PER_PIXEL 5 //lower for higher speed
# define MAX_TIME_JUMP 2000 // in milliseconds

# ifdef __APPLE__
# include "../mlx_macos/mlx.h"
# define ESC_K 53
# define LEFT_A 123
# define UP_A 126
# define RIGHT_A 124
# define G 5
# define W 12
# define A 1
# define D 2
# elif defined(__linux__)
# include "../mlx-linux/mlx.h"
# include <X11/keysym.h>
# define ESC_K XK_Escape
# define LEFT_A XK_Left
# define UP_A XK_Up
# define RIGHT_A XK_Right
# define G XK_g
# define A XK_a
# define D XK_d
# define W XK_w
# endif


typedef enum
{
	DROITE,
	HAUT,
	GAUCHE,
	BAS
} dir;

typedef struct s_player
{
	int		x;
	int 	y;
	dir 	dir;
	bool	jumping;
	long 	duration_jump;
	long	jump_timestop;
} t_player;

typedef struct s_img
{
	void	*img_ptr;
	char	*img_pixels_ptr;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_mlx
{
	void		*ptr;
	void		*window;
	t_img		image;
	t_player	*first_p;
	t_player	*second_p;
	int			countdown;
	long		last_time;
} t_mlx;
/*
Si countdown == -3, ecran de demarrage
Si countdown == -1, on joue
SI countdown == -2, stop jeu
...
*/

void 	init_data(t_mlx *data);
long	get_current_time_in_ms();

void	put_my_pixel(t_img *img, int x, int y, int color);
void	put_rectangle(t_img *img, int longueur, int largeur, int x, int y, int color);
void	put_square(t_img *img, int x, int y, int color);
void	clear_image(t_img *image);
int		get_pixel_color(t_img *img, int x, int y);

int		the_game(int key, t_mlx *data);
int		key_release(int key, t_mlx *data);
int		press_x(t_mlx *data);

int		render_loop(t_mlx *data);
void	check_death(t_mlx *data);

#endif
