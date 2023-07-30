/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:36:52 by zmoumen           #+#    #+#             */
/*   Updated: 2023/07/30 01:40:21 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "libft/libft.h"
# include "mlx42/include/MLX42/MLX42.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 800
# define WIN_TITLE "Cub3D"


typedef struct t_game
{
	mlx_t	*mlx;

}			t_game;
#endif
