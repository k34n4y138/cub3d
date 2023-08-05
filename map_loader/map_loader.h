/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 22:54:44 by zmoumen           #+#    #+#             */
/*   Updated: 2023/07/31 17:19:50 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_LOADER_H
# define MAP_LOADER_H
# define BLOC_SIZE 10
# include <stdint.h>
# include <stdlib.h>
# include "t_map.h"

t_map	load_map(char	*fpath);
#endif