/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:21:45 by zmoumen           #+#    #+#             */
/*   Updated: 2023/08/05 23:17:27 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "t_map.h"
#include <stdio.h>

#define MATRIX_CHARS "01NSEW "

void	validate_matrix_line(char	*mline, size_t lcount)
{
	int	found_charset;

	found_charset = 0;
	while (*mline && *mline != '\n')
	{
		if (!ft_strchr(MATRIX_CHARS, *mline))
		{
			printf("Found: %c at line: %zu!\n", *mline, lcount);
			ft_errmsg("Invalid character in matrix", 1);
		}
		if (*mline != ' ')
			found_charset = 1;
		mline++;
	}
	if (!found_charset)
	{
		printf("Empty line at line: %zu!\n", lcount);
		ft_errmsg("Map Matrix Should be Continuous", 1);
	}
}

void	set_player(t_map *map, size_t	x, size_t y, char dir)
{
	if (map->player.x != 0)
		ft_errmsg("Duplicate player position", 1);
	map->player.x = x;
	map->player.y = y;
	if (dir == 'E')
		map->player.dir = 0;
	else if (dir == 'N')
		map->player.dir = 90;
	else if (dir == 'W')
		map->player.dir = 180;
	else if (dir == 'S')
		map->player.dir = 270;
}

void	matrix_error(size_t y, size_t x, char *msg, t_map *map)
{
	size_t	errline;

	errline = map->f_lcount - map->m_lcount + y + 1;
	printf("Problem at y: %zu, x: %zu, Line %zu\n", y, x, errline);
	ft_errmsg(msg, 1);
}

void	validate_matrix_maze(t_map *map)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (map->matrix[y])
	{
		x = 0;
		while (map->matrix[y][x])
		{
			if (map->matrix[y][x] == ' ')
				(void)x;
			else if ((y * x == 0 || !map->matrix[y + 1]
					|| !map->matrix[y][x + 1]) && map->matrix[y][x] != '1')
				matrix_error(y, x, "Map should be surrounded by walls", map);
			else if (ft_strchr("NSEW0", map->matrix[y][x]) &&
			(map->matrix[y - 1][x] == ' ' || map->matrix[y + 1][x] == ' '
			|| map->matrix[y][x - 1] == ' ' || map->matrix[y][x + 1] == ' '))
				matrix_error(y, x, "Map should be surrounded by walls", map);
			if (ft_strchr("NSEW", map->matrix[y][x++]))
				set_player(map, x, y, map->matrix[y][x]);
		}
		y++;
	}
	if (map->player.x == 0)
		ft_errmsg("No player found", 1);
}

void	get_matrix(int fd, t_map	*map)
{
	char	*line;
	char	*tmp;

	line = map->_tx_paths[TEXTURE_MATRIX_TMP];
	tmp = ft_strdup("");
	if (line == NULL)
		ft_errmsg("No map found", 1);
	map->_tx_paths[TEXTURE_MATRIX_TMP] = NULL;
	while (line)
	{
		validate_matrix_line(line, map->f_lcount);
		map->m_lcount++;
		tmp = ft_strjoin_free(tmp, line, 1, 1);
		line = get_next_line(fd);
		if (line)
			map->f_lcount++;
	}
	map->matrix = ft_split(tmp, '\n');
	free(tmp);
	validate_matrix_maze(map);
}
