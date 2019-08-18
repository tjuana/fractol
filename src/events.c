/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 14:54:31 by tjuana            #+#    #+#             */
/*   Updated: 2019/08/09 16:06:24 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_zoom_n_iter(int key, t_stock *stock)
{
	if (key == 115 || key == 27)
		stock->mlx->zoom *= 1.5;
	else if (key == 119)
		stock->mlx->zoom /= 1.5;
	else if (key == 116 || key == 33)
		stock->mlx->iter += 10;
	else if (key == 121 && stock->mlx->iter > 100)
		stock->mlx->iter -= 10;
}

void	ft_move(int key, t_stock *stock)
{
	if (key == 126 && stock->mlx->move_y > -10000)
		stock->mlx->move_y += 0.05 / stock->mlx->zoom;
	else if (key == 125 && stock->mlx->move_y < 10000)
		stock->mlx-> move_y -= 0.05 / stock->mlx->zoom;
	else if (key == 123 && stock->mlx->move_x > -10000)
		stock->mlx->move_x += 0.05 / stock->mlx->zoom;
	else if (key == 124 && stock->mlx->move_x < 10000)
		stock->mlx->move_x -= 0.05 / stock->mlx->zoom;
}

void	ft_tutorial(t_stock *stock)
{
	mlx_string_put(stock->mlx->ptr, stock->mlx->win,
	stock->mlx->wid - 300, 25, 0xff7f24, "        BUTTONS");
	mlx_string_put(stock->mlx->ptr, stock->mlx->win,
	stock->mlx->wid - 300, 50, 0xff7f24, "ESC              quit");
	mlx_string_put(stock->mlx->ptr, stock->mlx->win,
	stock->mlx->wid - 300, 75, 0xff7f24, "R                reset");
	mlx_string_put(stock->mlx->ptr, stock->mlx->win,
	stock->mlx->wid - 300, 100, 0xff7f24, "TAB              next fractal");
	mlx_string_put(stock->mlx->ptr, stock->mlx->win,
	stock->mlx->wid - 300, 125, 0xff7f24, "PAGE UP / DOWN   iterations");
	mlx_string_put(stock->mlx->ptr, stock->mlx->win,
	stock->mlx->wid - 300, 150, 0xff7f24, "ARROWS           move");
	mlx_string_put(stock->mlx->ptr, stock->mlx->win,
	stock->mlx->wid - 300, 175, 0xff7f24, "HOME / END       zoom");
	mlx_string_put(stock->mlx->ptr, stock->mlx->win,
	stock->mlx->wid - 300, 200, 0xff7f24, "1 - 3            colors");
}

void	ft_reset(t_stock *stock)
{
	stock->mlx->zoom = 1;
	stock->mlx->move_x = -0.5;
	stock->mlx->move_y = 0;
	stock->mlx->iter = 100;
	stock->mlx->julia.x = -0.835;
	stock->mlx->julia.y = -0.2321;
}

int		ft_key(int key, t_stock *stock)
{
	if (key == 53)
		exit(0);
	else if (key == 15)
		ft_reset(stock);
	else if (key >= 18 && key <= 20)
		stock->mlx->choise_pan = key - 18;
	else if (key == 48)
		stock->mlx->fractol = (stock->mlx->fractol + 1) % 9;
	ft_zoom_n_iter(key, stock);
	ft_move(key, stock);
	ft_bzero(stock->mlx->str,
			stock->mlx->wid * stock->mlx->heig * sizeof(int));
	ft_put_fractol_to_img(stock);
	mlx_put_image_to_window(stock->mlx->ptr, stock->mlx->win,
			stock->mlx->img, 0, 0);
	ft_tutorial(stock);
	return (0);
}
