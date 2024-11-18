
#include "play.h"

void	put_my_pixel(t_img *img, int x, int y, int color)
{
    int	decalage;

	if (x >= WIDTH)
		x -= WIDTH;
	if (x < 0)
		x += WIDTH;
	if (y >= HEIGHT)
		y -= HEIGHT;
	if (y < 0)
		y += HEIGHT;
	decalage = (y * img->line_len) + (x * (img->bits_per_pixel / 8));
	*((unsigned int *)(img->img_pixels_ptr + decalage)) = color;
}

void put_square(t_img *img, int x, int y, int color)
{
	int ix = 0;
	int iy = 0;

	while (ix < SQUARE_SIZE)
	{
		iy = 0;
		while (iy < SQUARE_SIZE)
		{
			put_my_pixel(img, x + ix, y + iy, color);
			iy++;
		}
		ix++;
	}
}

void put_rectangle(t_img *img, int longueur, int largeur, int x, int y, int color)
{
	int ix = 0;
	int iy = 0;

	while (ix < longueur)
	{
		iy = 0;
		while (iy < largeur)
		{
			put_my_pixel(img, x + ix, y + iy, color);
			iy++;
		}
		ix++;
	}
}

void clear_image(t_img *image)
{
    int x, y;
    int color = 0x000000;

    for (y = 0; y < HEIGHT; y++)
	{
        for (x = 0; x < WIDTH; x++)
            put_my_pixel(image, x, y, color);
    }
}

int get_pixel_color(t_img *img, int x, int y)
{
    int offset = (y * img->line_len) + (x * (img->bits_per_pixel / 8));
    
    int color;
    if (img->endian == 0)
	{
        color = *(unsigned int *)(img->img_pixels_ptr + offset);
    }
	else
	{
        color = (img->img_pixels_ptr[offset] << 24) | 
                (img->img_pixels_ptr[offset + 1] << 16) | 
                (img->img_pixels_ptr[offset + 2] << 8) | 
                (img->img_pixels_ptr[offset + 3]);
    }
    return (color);
}