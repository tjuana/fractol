/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 12:42:13 by tjuana            #+#    #+#             */
/*   Updated: 2019/08/10 12:11:17 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ft_htr_help(t_color *c, double v1, double v2, double v3)
{
	c->r = v1;
	c->g = v2;
	c->b = v3;
}

int			ft_hsv_to_rgb(double h, double s, double v, int pan)
{
	t_color		c;

	c.i = (int)h;
	c.f = h * 6 - c.i;
	c.p = v * (1 - s);
	c.q = v * (1 - c.f * s);
	c.t = v * (1 - (1 - c.f) * s);
	if (c.i % 6 == 0)
		ft_htr_help(&c, v, c.t, c.p);
	else if (c.i % 6 == 1)
		ft_htr_help(&c, c.q, v, c.p);
	else if (c.i % 6 == 2)
		ft_htr_help(&c, c.p, v, c.t);
	else if (c.i % 6 == 3)
		ft_htr_help(&c, c.p, c.q, v);
	else if (c.i % 6 == 4)
		ft_htr_help(&c, c.t, c.p, v);
	else
		ft_htr_help(&c, v, c.p, c.q);
	if (pan == 0)
		return (c.r * 0xff0000 + c.g * 0x00ff00 + c.b * 0x0000ff);
	else if (pan == 1)
		return (c.b * 0xff0000 + c.r * 0x00ff00 + c.g * 0x0000ff);
	else
		return (c.g * 0xff0000 + c.b * 0x00ff00 + c.r * 0x0000ff);
}

void		ft_fill_pixel(t_mlx *mlx, int x, int y, int color)
{
	if (x >= 0 && y >= 0 && x < mlx->wid && y < mlx->heig)
		mlx->str[x + mlx->wid * y] = color;
}

void		ft_put_fractol_to_img(t_stock *stock)
{
	t_threads	th_tab[THREADS];
	void		*f;
	int			i;

	stock->mlx->fractol == 0 ? f = ft_mandelbrot : 0;
	stock->mlx->fractol == 1 ? f = ft_julia : 0;
	stock->mlx->fractol == 2 ? f = ft_burning_ship : 0;
	stock->mlx->fractol == 3 ? f = ft_tricorn : 0;
	stock->mlx->fractol == 4 ? f = ft_thunder : 0;
	stock->mlx->fractol == 5 ? f = ft_bubble : 0;
	stock->mlx->fractol == 7 ? f = ft_feather : 0;
	stock->mlx->fractol == 6 ? f = ft_shell : 0;
	stock->mlx->fractol == 8 ? f = ft_cube : 0;
	i = 0;
	while (i < THREADS)
	{
		th_tab[i].n = i;
		th_tab[i].mlx = stock->mlx;
		pthread_create(&(th_tab[i].id), NULL, f, (void *)&(th_tab[i]));
		i++;
	}
	i = 0;
	while (i < THREADS)
		pthread_join(th_tab[i++].id, NULL);
}
