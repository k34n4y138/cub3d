/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 00:55:29 by zmoumen           #+#    #+#             */
/*   Updated: 2023/08/11 00:36:03 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_MAP_H
# define T_MAP_H
# include <stdint.h>
# include <MLX42.h>

typedef struct s_player
{
	double		x;
	double		y;
	double		dir;
}			t_player;

enum e_texture_index
{
	TEXTURE_NORTH,
	TEXTURE_SOUTH,
	TEXTURE_EAST,
	TEXTURE_WEST,
	TEXTURE_FLOOR,
	TEXTURE_CEILING,
	TEXTURE_MATRIX_TMP
};

typedef struct s_map
{
	size_t			f_lcount;
	size_t			m_lcount;
	size_t			m_width;
	char			*_tx_paths[7];
	mlx_image_t		*textures[6];
	char			**matrix;
	t_player		player;
}				t_map;

#endif