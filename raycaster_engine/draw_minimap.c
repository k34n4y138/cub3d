/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 11:35:58 by yowazga           #+#    #+#             */
/*   Updated: 2023/08/11 03:17:55 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_colom(int i, int j, t_game *cub, int status)
{
	int	a;
	int	b;
	int	save;

	a = i + (TILE_SIZE * MINIMAP);
	while (i <= a)
	{
		b = j + (TILE_SIZE * MINIMAP);
		save = j;
		while (save <= b)
		{
			if (status)
				mlx_put_pixel(cub->image, save, i, ft_pixel(47, 79,79, 255));
			else if (!status)
			{
				if (save == b || i == a)
					mlx_put_pixel(cub->image, save, i,
						ft_pixel(173, 216, 230, 255));
				else
					mlx_put_pixel(cub->image, save, i, 0xffffffff);
			}
			save++;
		}
		i++;
	}
}

void	draw_map(t_game *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->map.m_lcount)
	{
		j = 0;
		while (j < cub->map.m_width)
		{
			if (cub->map.matrix[i][j] == '1')
				draw_colom(MINIMAP * (i * TILE_SIZE), MINIMAP * ( j * TILE_SIZE), cub, 1);
			else if (cub->map.matrix[i][j] == '0')
				draw_colom(MINIMAP * (i * TILE_SIZE), MINIMAP * ( j * TILE_SIZE), cub, 0);
			j++;
		}
		i++;
	}
}

void	init_lin_player(t_game *cub, t_argline *arg)
{
	arg->x0 = cub->player.x * MINIMAP;
	arg->y0 = cub->player.y * MINIMAP;
	arg->x1 = (cub->player.x + cos(cub->player.rorationangle) * 25) * MINIMAP;
	arg->y1 = (cub->player.y + sin(cub->player.rorationangle) * 25) * MINIMAP;
	arg->color = ft_pixel(255, 38, 60, 255);
	draw_line(cub, *arg);
}

void	draw_player(t_game *cub)
{
	int		x;
	int		y;
	int		dx;
	int		dy;
	int		distance_squared;

	x = (cub->player.x - cub->player.radius) * MINIMAP;
	while (x < (cub->player.x + cub->player.radius) * MINIMAP)
	{
		y = (cub->player.y - cub->player.radius) * MINIMAP;
		while (y < (cub->player.y + cub->player.radius) * MINIMAP)
		{
			dx = x - cub->player.x * MINIMAP;
			dy = y - cub->player.y * MINIMAP;
			distance_squared = dx * dx + dy * dy;
			if (distance_squared < (cub->player.radius * cub->player.radius) * MINIMAP)
				mlx_put_pixel(cub->image, x, y, ft_pixel(255, 38, 60, 255));
			y++;
		}
		x++;
	}
}

void	cast_all_rays(t_game *cub)
{
	double		rayangle;
	int			i;
	t_argline	arg;

	i = 0;
	rayangle = cub->player.rorationangle - (FOV_ANGLE / 2);
	while (i++ < NUM_RAYS)
	{
		cast_ray(cub, rayangle);
		handl_err_pixl(cub);
		arg.x0 = cub->player.x * MINIMAP;
		arg.x1 = cub->cast.wal_x * MINIMAP;
		arg.y0 = cub->player.y * MINIMAP;
		arg.y1 = cub->cast.wal_y * MINIMAP;
		arg.color = ft_pixel(173, 216, 230, 255);
		draw_line(cub, arg);
		rayangle += FOV_ANGLE / NUM_RAYS;
	}
}
