/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractols5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:32:31 by tjuana            #+#    #+#             */
/*   Updated: 2019/08/09 16:50:09 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ft_cube_help(t_threads *t, t_coord c, t_complex cst)
{
	t_complex	n;
	t_complex	o;

	n.x = 1.5 * (c.x - t->mlx->wid / 2)
		/ (0.5 * t->mlx->zoom * t->mlx->wid) + t->mlx->move_x + 0.5;
	n.y = (c.y - t->mlx->heig / 2)
		/ (0.5 * t->mlx->zoom * t->mlx->heig) + t->mlx->move_y;
	t->i = 0;
	while (t->i < t->mlx->iter)
	{
		o.x = n.x;
		o.y = n.y;
		n.x = o.x * o.x * o.x - 3 * o.x * o.y * o.y + cst.x;
		n.y = 3 * o.x * o.x * o.y - o.y * o.y * o.y + cst.y;
		if (n.x * n.x + n.y * n.y > 4)
			break ;
		t->i++;
	}
}

void		*ft_cube(void *threadv)
{
	t_coord		c;
	t_complex	cst;
	t_threads	*t;

	t = (t_threads *)threadv;
	cst.x = t->mlx->julia.x;
	cst.y = t->mlx->julia.y;
	c.y = t->n * t->mlx->heig / THREADS;
	t->max = (t->n + 1) * t->mlx->heig / THREADS;
	while (c.y < t->max)
	{
		c.x = 0;
		while (c.x < t->mlx->wid)
		{
			ft_cube_help(t, c, cst);
			ft_fill_pixel(t->mlx, c.x, c.y, ft_hsv_to_rgb(4 * t->i / 255.0, 1,
						t->i < t->mlx->iter, t->mlx->choise_pan));
			c.x++;
		}
		c.y++;
	}
	pthread_exit(NULL);
	return (NULL);
}
