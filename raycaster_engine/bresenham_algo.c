#include <cub3d.h>

void	init_arg_line(t_line *line, t_argline *arg)
{
	line->dx = abs(arg->x1 - arg->x0);
	line->dy = abs(arg->y1 - arg->y0);
	if (arg->x0 < arg->x1)
		line->sx = 1;
	else
		line->sx = -1;
	if (arg->y0 < arg->y1)
		line->sy = 1;
	else
		line->sy = -1;
	if (line->dx > line->dy)
		line->err = line->dx / 2;
	else
		line->err = -line->dy / 2;
}

void	draw_line(t_game *cub, t_argline arg)
{
	t_line	line;

	init_arg_line(&line, &arg);
	while (1)
	{
		if (arg.x0 >= 0 && arg.x0 < WIN_WIDTH && arg.y0 >= 0 && arg.y0 < WIN_HEIGHT)
			mlx_put_pixel(cub->image, arg.x0, arg.y0, arg.color);
		if (arg.x0 == arg.x1 && arg.y0 == arg.y1)
			break ;
		line.e2 = line.err;
		if (line.e2 > -line.dx)
		{
			line.err -= line.dy;
			arg.x0 += line.sx;
		}
		if (line.e2 < line.dy)
		{
			line.err += line.dx;
			arg.y0 += line.sy;
		}
	}
}
