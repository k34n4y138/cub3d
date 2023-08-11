#include <cub3d.h>

void	init_hor_content(t_game *cub)
{
	cub->cast.horwallhilt_x = 0;
	cub->cast.horwallhilt_y = 0;
	cub->cast.fondhorwal = 0;
	cub->cast.y_intercept = (((int)cub->player.y / TILE_SIZE) * TILE_SIZE);
	if (cub->cast.is_down)
		cub->cast.y_intercept += TILE_SIZE;
	else
		cub->cast.y_intercept += 0;
	cub->cast.x_intercept = cub->player.x
		+ ((cub->cast.y_intercept - cub->player.y) / tan(cub->cast.rayangle));
	cub->cast.dy = TILE_SIZE;
	if (cub->cast.is_up)
		cub->cast.dy *= -1;
	else
		cub->cast.dy *= 1;
	cub->cast.dx = (TILE_SIZE / tan(cub->cast.rayangle));
	if (cub->cast.is_left && cub->cast.dx > 0)
		cub->cast.dx *= -1;
	else
		cub->cast.dx *= 1;
	if (cub->cast.is_right && cub->cast.dx < 0)
		cub->cast.dx *= -1;
	else
		cub->cast.dx *= 1;
}

void	handl_recast_horizontal(t_game *cub)
{
	float	next_hor_x;
	float	next_hor_y;

	init_hor_content(cub);
	next_hor_x = cub->cast.x_intercept;
	next_hor_y = cub->cast.y_intercept;
	while (next_hor_x >= 0 && next_hor_x <= WIN_WIDTH
		&& next_hor_y >= 0 && next_hor_y <= WIN_HEIGHT)
	{
		if (!check_wall(&cub->map, next_hor_x,  next_hor_y - (cub->cast.is_up ? 1 : 0)))
		{
			cub->cast.fondhorwal = 1;
			cub->cast.horwallhilt_x = next_hor_x;
			cub->cast.horwallhilt_y = next_hor_y;
			break ;
		}
		else
		{
			next_hor_x += cub->cast.dx;
			next_hor_y += cub->cast.dy;
		}
	}
}

void	init_ver_content(t_game *cub)
{
	cub->cast.verwallhilt_x = 0;
	cub->cast.verwallhilt_y = 0;
	cub->cast.fondverwal = 0;
	cub->cast.x_intercept = (((int)cub->player.x / TILE_SIZE) * TILE_SIZE);
	if (cub->cast.is_right)
		cub->cast.x_intercept += TILE_SIZE;
	else
		cub->cast.x_intercept += 0;
	cub->cast.y_intercept = cub->player.y
		+ ((cub->cast.x_intercept - cub->player.x) * tan(cub->cast.rayangle));
	cub->cast.dx = TILE_SIZE;
	if (cub->cast.is_left)
		cub->cast.dx *= -1;
	else
		cub->cast.dx *= 1;
	cub->cast.dy = (TILE_SIZE * tan(cub->cast.rayangle));
	if (cub->cast.is_up && cub->cast.dy > 0)
		cub->cast.dy *= -1;
	else
		cub->cast.dy *= 1;
	if (cub->cast.is_down && cub->cast.dy < 0)
		cub->cast.dy *= -1;
	else
		cub->cast.dy *= 1;
}

void	handl_recast_vertical(t_game *cub)
{
	float	next_ver_x;
	float	next_ver_y;

	init_ver_content(cub);
	next_ver_x = cub->cast.x_intercept;
	next_ver_y = cub->cast.y_intercept;
	while (next_ver_x >= 0 && next_ver_x <= WIN_WIDTH
		&& next_ver_y >= 0 && next_ver_y <= WIN_HEIGHT)
	{
		if (!check_wall(&cub->map, next_ver_x - (cub->cast.is_left ? 1 : 0), next_ver_y))
		{
			cub->cast.fondverwal = 1;
			cub->cast.verwallhilt_x = next_ver_x;
			cub->cast.verwallhilt_y = next_ver_y;
			break ;
		}
		else
		{
			next_ver_x += cub->cast.dx;
			next_ver_y += cub->cast.dy;
		}
	}
}
