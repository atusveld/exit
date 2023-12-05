/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 14:44:11 by atusveld      #+#    #+#                 */
/*   Updated: 2023/02/16 19:22:19 by atusveld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_check_map(t_sl *sl)
{
	int			e;
	int			p;
	int			x;
	int			xx;
	int			y;

	y = 0;
	e = 0;
	p = 0;
	xx = ft_strlen(sl->map[0]);
	while (sl->map[y] != NULL)
	{
		x = 0;
		while (sl->map[y][x] != '\0')
		{
			if (sl->map[y][x] == 'C')
				sl->tc += 1;
			if (sl->map[y][x] == 'P')
			{
				sl->x = x;
				sl->y = y;
				p += 1;
			}
			if (sl->map[y][x] == 'E')
				e += 1;
			x++;
		}
		if (x != xx)
			ft_error(MAP);
		y++;
	}
	if (sl->tc < 1 || e < 1 || p < 1)
		ft_error(MAP);
	ft_walls(sl, xx, y);
}

void	ft_walls(t_sl *sl, int xx, int yy)
{
	int		x;
	int		y;
	int		v;

	v = 0;
	y = 0;
	while (sl->map[y] != NULL)
	{
		x = 0;
		while (sl->map[y][x] != '\0')
		{
			if (sl->map[0][x] != '1' || sl->map[yy - 1][x] != '1')
				ft_error(MAP);
			if (sl->map[y][0] != '1' || sl->map[y][xx - 1] != '1')
				ft_error(MAP);
			x++;
		}
		y++;
	}
	v = ft_pathfinder(sl, sl->x, sl->y);
	if (v == 0)
		ft_error(MAP);
	if (sl->fc != sl->tc)
		ft_error(MAP);
}

#include <stdio.h>

int	ft_pathfinder(t_sl *sl, int x, int y)
{
	int		rt;

	rt = 0;
	if (sl->map2[y][x] == '1')
		return (0);
	if (sl->map2[y][x] != '\0')
	{
		if (sl->map2[y][x] == 'C')
			sl->fc += 1;
		if (sl->map2[y][x] == 'E')
			return (1);
		sl->map2[y][x] = '1';
		rt += ft_pathfinder(sl, x + 1, y);
		rt += ft_pathfinder(sl, x, y + 1);
		rt += ft_pathfinder(sl, x - 1, y);
		rt += ft_pathfinder(sl, x, y - 1);
	}
	return (rt);
}

//- valid path possible C, E