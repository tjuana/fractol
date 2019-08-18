/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 14:57:09 by tjuana            #+#    #+#             */
/*   Updated: 2019/08/09 13:01:57 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_mouse_zoom(int key, int x, int y, t_stock *stock)
{
	if (x > 0 && x < stock->mlx->wid && y > 0 && y < stock->mlx->wid)
	{
		if (key == 4)
		{
			stock->mlx->zoom *= 1.5;
		}
		else if (key == 5)
		{
			stock->mlx->zoom /= 1.5;
		}
	}
	ft_bzero(stock->mlx->str,
			stock->mlx->wid * stock->mlx->heig * sizeof(int));
	ft_put_fractol_to_img(stock);
	mlx_put_image_to_window(stock->mlx->ptr, stock->mlx->win, stock->mlx->img,
			0, 0);
	ft_tutorial(stock);
	return (0);
}

int		ft_mouse_event(int x, int y, t_stock *stock)
{
	if (stock->mlx->fractol != 1 && stock->mlx->fractol != 8)
		return (0);
	if (x > 0 && x < stock->mlx->wid && y > 0 && y < stock->mlx->heig)
	{
		stock->mlx->julia.x = (double)x / stock->mlx->wid * 2 - 1;
		stock->mlx->julia.y = (double)y / stock->mlx->heig * 2 - 1;
		ft_putstr("c = ");
		ft_putdbl(stock->mlx->julia.x, 3);
		ft_putstr(" + ");
		ft_putdbl(stock->mlx->julia.y, 3);
		ft_putendl("i");
	}
	ft_bzero(stock->mlx->str,
			stock->mlx->wid * stock->mlx->heig * sizeof(int));
	ft_put_fractol_to_img(stock);
	mlx_put_image_to_window(stock->mlx->ptr, stock->mlx->win, stock->mlx->img,
			0, 0);
	ft_tutorial(stock);
	return (0);
}
