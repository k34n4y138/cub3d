/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:29:00 by zmoumen           #+#    #+#             */
/*   Updated: 2023/08/11 03:48:00 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_content(t_game *cub)
{
	t_argline	arg;

	init_image(cub);
	draw_3d_map(cub);
	draw_map(cub);
	cast_all_rays(cub);
	init_lin_player(cub, &arg);
	draw_player(cub);
}

int	init_content(t_game *cub, char *path)
{
	cub->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "CUB3D", true);
	if (!cub->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	cub->image = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cub->image)
	{
		mlx_close_window(cub->mlx);
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	if (mlx_image_to_window(cub->mlx, cub->image, 0, 0) == -1)
	{
		mlx_close_window(cub->mlx);
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	cub->map = load_map(path);
	cub->player = cub->map.player;
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		ft_errmsg("Please provide one map[.ber] file", 1);
	ft_bzero(&game, sizeof(t_game));
	if (init_content(&game, av[1]))
		return (1);
	draw_content(&game);
	mlx_loop_hook(game.mlx, ft_hook, &game);
	mlx_key_hook(game.mlx, &my_keyhook, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
