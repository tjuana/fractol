/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractols2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 14:52:38 by tjuana            #+#    #+#             */
/*   Updated: 2019/08/09 16:12:39 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ft_tricorn_help(t_threads *t, t_coord c)
{
	t_complex	p;
	t_complex	new;
	t_complex	old;

	p.x = 1.5 * (c.x - t->mlx->wid / 2)
		/ (0.5 * t->mlx->zoom * t->mlx->wid / 1.5) + t->mlx->move_x;
	p.y = (c.y - t->mlx->heig / 2)
		/ (0.5 * t->mlx->zoom * t->mlx->heig / 1.5) + t->mlx->move_y;
	new.x = 0;
	new.y = 0;
	t->i = 0;
	while (t->i < t->mlx->iter)
	{
		old.x = new.x;
		old.y = new.y;
		new.x = old.x * old.x - old.y * old.y + p.x;
		new.y = -2 * old.x * old.y + p.y;
		if (new.x * new.x + new.y * new.y > 4)
			break ;
		t->i++;
	}
}

void		*ft_tricorn(void *threadv)
{
	t_coord		c;
	t_threads	*t;

	t = (t_threads *)threadv;
	c.y = t->n * t->mlx->heig / THREADS;
	t->max = (t->n + 1) * t->mlx->heig / THREADS;
	while (c.y < t->max)
	{
		c.x = 0;
		while (c.x < t->mlx->wid)
		{
			ft_tricorn_help(t, c);
			ft_fill_pixel(t->mlx, c.x, c.y, ft_hsv_to_rgb(t->i / 255.0, 1,
						t->i < t->mlx->iter, t->mlx->choise_pan));
			c.x++;
		}
		c.y++;
	}
	pthread_exit(NULL);
	return (NULL);
}

static void	ft_thunder_help(t_threads *t, t_coord c, t_complex cst)
{
	t_complex	new;
	t_complex	old;

	new.x = 1.5 * (c.x - t->mlx->wid / 2)
		/ (0.5 * t->mlx->zoom * t->mlx->wid / 1.5) + t->mlx->move_x + 0.5;
	new.y = (c.y - t->mlx->heig / 2)
		/ (0.5 * t->mlx->zoom * t->mlx->heig / 1.5) + t->mlx->move_y;
	t->i = 0;
	while (t->i < t->mlx->iter)
	{
		old.x = new.x;
		old.y = new.y;
		new.x = old.x * old.x - old.y * old.y + cst.x;
		new.y = 2 * old.x * old.y + cst.y;
		if (new.x * new.x + new.y * new.y > 4)
			break ;
		t->i++;
	}
}

void		*ft_thunder(void *threadv)
{
	t_coord		c;
	t_complex	cst;
	t_threads	*t;

	t = (t_threads *)threadv;
	cst.x = 0.0;
	cst.y = 1.0;
	c.y = t->n * t->mlx->heig / THREADS;
	t->max = (t->n + 1) * t->mlx->heig / THREADS;
	while (c.y < t->max)
	{
		c.x = 0;
		while (c.x < t->mlx->wid)
		{
			ft_thunder_help(t, c, cst);
			ft_fill_pixel(t->mlx, c.x, c.y, ft_hsv_to_rgb(2 * t->i / 255.0, 1,
					t->i < t->mlx->iter, t->mlx->choise_pan));
			c.x++;
		}
		c.y++;
	}
	pthread_exit(NULL);
	return (NULL);
}
