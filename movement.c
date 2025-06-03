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

void	rotate_vector(double *px, double *py, double angle)
{
	double	old_x;
	double	cos_a;
	double	sin_a;

	old_x = *px;
	cos_a = cos(angle);
	sin_a = sin(angle);
	*px = old_x * cos_a - *py * sin_a;
	*py = old_x * sin_a + *py * cos_a;
}

void	update_player_rotation(t_data *d)
{
	double	rs;

	rs = ROT_SPEED;
	if (d->player->turn_left != 0)
	{
		rotate_vector(&d->player->dir_x, &d->player->dir_y, -rs);
		rotate_vector(&d->player->plane_x, &d->player->plane_y, -rs);
	}
	if (d->player->turn_right != 0)
	{
		rotate_vector(&d->player->dir_x, &d->player->dir_y, rs);
		rotate_vector(&d->player->plane_x, &d->player->plane_y, rs);
	}
}


void	compute_new_position(t_player *p, double *nx, double *ny)
{
	*nx = p->x;
	*ny = p->y;
	if (p->move_up != 0)
	{
		*nx = *nx + p->dir_x * SPEED;
		*ny = *ny + p->dir_y * SPEED;
	}
	if (p->move_down != 0)
	{
		*nx = *nx - p->dir_x * SPEED;
		*ny = *ny - p->dir_y * SPEED;
	}
	if (p->move_right != 0)
	{
		*nx = *nx + p->plane_x * SPEED;
		*ny = *ny + p->plane_y * SPEED;
	}
	if (p->move_left != 0)
	{
		*nx = *nx - p->plane_x * SPEED;
		*ny = *ny - p->plane_y * SPEED;
	}
}

void	update_player_pos(t_data *d)
{
	double	nx;
	double	ny;
	int		tx;
	int		ty;

	compute_new_position(d->player, &nx, &ny);
	tx = (int)nx;
	ty = (int)ny;
	if (tx < 0 || tx >= d->x || ty < 0 || ty >= d->y)
		return ;
	if (d->map[ty][tx] == '1')
		return ;
	d->player->x = nx;
	d->player->y = ny;
}
