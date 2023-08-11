/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 00:51:19 by zmoumen           #+#    #+#             */
/*   Updated: 2023/08/11 02:57:02 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*skip_empty_lines(int fd, int *lcount)
{
	char		*line;
	int		i;

	line = get_next_line(fd);
	while (line)
	{
		if (lcount)
			(*lcount)++;
		i = 0;
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i] != '\0' && line[i] != '\n')
			break ;
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}
