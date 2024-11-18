
#include "play.h"

int		press_x(t_mlx *data)
{
	free(data->first_p);
	free(data->second_p);
	mlx_destroy_image(data->ptr, data->image.img_ptr);
	mlx_destroy_window(data->ptr, data->window);
	exit (0);
}

long get_current_time_in_ms()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec * 1000 + time.tv_usec / 1000;
}