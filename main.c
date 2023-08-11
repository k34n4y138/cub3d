/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:29:00 by zmoumen           #+#    #+#             */
/*   Updated: 2023/08/11 01:05:06 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int ac, char **av)
{
	t_game	game;
	t_map	map;

	if (ac != 2)
		ft_errmsg("Please provide one map[.ber] file", 1);
	map = load_map(av[1]);
	ft_bzero(&game, sizeof(t_game));
	game.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE, false);
	(void)game;
	mlx_loop(game.mlx);
	return (0);
}
