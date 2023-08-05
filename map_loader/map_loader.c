/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 20:03:40 by zmoumen           #+#    #+#             */
/*   Updated: 2023/08/05 20:10:35 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_loader.h"
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "libft.h"
#include "_map_internal.h"

int	open_cub_file(char	*fpath)
{
	int		fd;
	size_t	slen;

	if (fpath == NULL)
		ft_errmsg("File path is NULL", 1);
	slen = ft_strlen(fpath);
	if (slen < 4 || ft_strncmp(fpath + slen - 4, ".cub", 4) != 0)
		ft_errmsg("File extension is not .cub", 1);
	fd = open(fpath, O_RDONLY);
	if (fd == -1)
		ft_errmsg(strerror(errno), 1);
	return (fd);
}

t_map	load_map(char *fpath)
{
	int		fd;
	t_map	map;

	fd = open_cub_file(fpath);
	ft_bzero(&map, sizeof(t_map));
	get_textures(&map, fd);
	get_matrix(fd, &map);
	return (map);
}