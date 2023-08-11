/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 00:47:12 by zmoumen           #+#    #+#             */
/*   Updated: 2023/08/11 01:01:55 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42.h>
# include "libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <libft.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>

# define WIN_WIDTH 800
# define WIN_HEIGHT 800
# define WIN_TITLE "Cub3D"
# define BLOCK_SIZE 64


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


typedef struct t_game
{
	mlx_t	*mlx;
}			t_game;


int		open_cub_file(char *fpath);
void	get_textures(t_map *map, int fd);
void	get_matrix(int fd, t_map	*map);
char	*skip_empty_lines(int fd, size_t *lcount);

t_map	load_map(char	*fpath);

#endif