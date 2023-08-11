#include <cub3d.h>

void	calculate_distances(t_game *cub)
{
	if (cub->cast.fondhorwal)
		cub->cast.hordistance = distance_two_poins(cub->player.x, \
			cub->player.y, cub->cast.horwallhilt_x, cub->cast.horwallhilt_y);
	else
		cub->cast.hordistance = INT_MAX;
	if (cub->cast.fondverwal)
		cub->cast.verdistance = distance_two_poins(cub->player.x, \
			cub->player.y, cub->cast.verwallhilt_x, cub->cast.verwallhilt_y);
	else
		cub->cast.verdistance = INT_MAX;
	if (cub->cast.verdistance < cub->cast.hordistance)
	{
		cub->cast.wal_x = cub->cast.verwallhilt_x;
		cub->cast.wal_y = cub->cast.verwallhilt_y;
		cub->cast.distance = cub->cast.verdistance;
		cub->cast.washitvertical = 1;
	}
	else
	{
		cub->cast.wal_x = cub->cast.horwallhilt_x;
		cub->cast.wal_y = cub->cast.horwallhilt_y;
		cub->cast.distance = cub->cast.hordistance;
		cub->cast.washitvertical = 0;
	}
}

void	cast_ray(t_game *cub, float rayangle)
{
	cub->cast.rayangle = norm_angle(rayangle);
	cub->cast.wal_x = 0;
	cub->cast.wal_y = 0;
	cub->cast.distance = 0;
	cub->cast.washitvertical = 0;
	if (cub->cast.rayangle > 0 && cub->cast.rayangle < M_PI)
		cub->cast.is_down = 1;
	else
		cub->cast.is_down = 0;
	cub->cast.is_up = !cub->cast.is_down;
	if (cub->cast.rayangle < 0.5 * M_PI || cub->cast.rayangle > 1.5 * M_PI)
		cub->cast.is_right = 1;
	else
		cub->cast.is_right = 0;
	cub->cast.is_left = !cub->cast.is_right;
	handl_recast_horizontal(cub);
	handl_recast_vertical(cub);
	calculate_distances(cub);
}

void	init_image(t_game *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < cub->image->height)
	{
		x = 0;
		while (x < cub->image->width)
		{
			if (y < cub->image->height / 2)
				mlx_put_pixel(cub->image, x++, y, ft_pixel(135, 206,250, 255));
			else if (y < cub->image->height)
				mlx_put_pixel(cub->image, x++, y, ft_pixel(46, 139,87, 255));
		}
		y++;
	}
}

void	draw_3d_map(t_game *cub)
{
	t_argline	arg;
	float		rayangle;
	int			color;
	int			i;

	i = -1;
	rayangle = cub->player.rorationangle - (FOV_ANGLE / 2);
	arg.distance = (WIN_WIDTH / 2) / tan(FOV_ANGLE / 2);
	while (++i < NUM_RAYS)
	{
		cast_ray(cub, rayangle);
		arg.cor_dis = cub->cast.distance * cos(rayangle - cub->player.rorationangle);
		arg.wal_height = (TILE_SIZE / arg.cor_dis) * arg.distance;
		if (arg.wal_height > WIN_HEIGHT)
			arg.wal_height = WIN_HEIGHT;
		arg.x0 = i;
		arg.x1 = i;
		arg.y0 = (WIN_HEIGHT / 2) - (arg.wal_height / 2);
		arg.y1 = (WIN_HEIGHT / 2) + (arg.wal_height / 2);
		if (cub->cast.washitvertical)
			arg.color = ft_pixel(205, 133, 63, 255);
		else
			arg.color = ft_pixel(210, 105, 30, 255);
		draw_line(cub, arg);
		rayangle += FOV_ANGLE / NUM_RAYS;
	}
}
