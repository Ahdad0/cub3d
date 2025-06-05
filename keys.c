#include "cub3d.h"

int	key_press(int keycode, t_data *d)
{
	// printf("%d\n", keycode);
	if(keycode == MOVE_UP)
		d->player->move_up = 1;
	if(keycode == MOVE_DOWN)
		d->player->move_down = 1;
	if(keycode == MOVE_RIGHT)
		d->player->move_right = 1;
	if(keycode == MOVE_LEFT)
		d->player->move_left = 1;
	if(keycode == TURN_LEFT)
		d->player->turn_left = 1;
	if(keycode == TURN_RIGHT)
		d->player->turn_right = 1;
	if (keycode == ECHAP) 
		close_window(d);
	return(0);
}

int	key_release(int keycode, t_data *d)
{
	if(keycode == MOVE_UP)
		d->player->move_up = 0;
	if(keycode == MOVE_DOWN)
		d->player->move_down = 0;
	if(keycode == MOVE_RIGHT)
		d->player->move_right = 0;
	if(keycode == MOVE_LEFT)
		d->player->move_left = 0;
	if(keycode == TURN_LEFT)
		d->player->turn_left = 0;
	if(keycode == TURN_RIGHT)
		d->player->turn_right = 0;
	return(0);
}
