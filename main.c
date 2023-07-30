/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:29:00 by zmoumen           #+#    #+#             */
/*   Updated: 2023/07/30 01:41:33 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	main(int ac, char **av)
{
	t_game	game;

	(void)ac;
	(void)av;
	ft_bzero(&game, sizeof(t_game));
	game.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE, false);

	mlx_loop(game.mlx);
	return (0);
}
