/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _map_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 00:48:47 by zmoumen           #+#    #+#             */
/*   Updated: 2023/08/05 20:07:39 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MAP_INTERNAL_H
# define _MAP_INTERNAL_H
# include "t_map.h"

int		open_cub_file(char *fpath);
void	get_textures(t_map *map, int fd);
void	get_matrix(int fd, t_map	*map);
char	*skip_empty_lines(int fd, size_t *lcount);
#endif