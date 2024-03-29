/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 11:48:48 by tjuana            #+#    #+#             */
/*   Updated: 2019/08/09 16:50:16 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_choise(char *file)
{
	if (ft_strequ(file, "mandelbrot"))
		return (0);
	else if (ft_strequ(file, "julia"))
		return (1);
	else if (ft_strequ(file, "burningship"))
		return (2);
	else if (ft_strequ(file, "tricorn"))
		return (3);
	else if (ft_strequ(file, "thunder"))
		return (4);
	else if (ft_strequ(file, "bubble"))
		return (5);
	else if (ft_strequ(file, "shell"))
		return (6);
	else if (ft_strequ(file, "feather"))
		return (7);
	else if (ft_strequ(file, "cube"))
		return (8);
	return (-1);
}

t_mlx	*ft_mlx_setup(char *title)
{
	t_mlx	*mlx;
	int		bpp;
	int		s_l;
	int		endian;

	if (!(mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		return (NULL);
	if ((mlx->fractol = ft_choise(title)) == -1)
		return (NULL + ft_usage());
	mlx->ptr = mlx_init();
	mlx->wid = 1280;
	mlx->heig = 720;
	mlx->img = mlx_new_image(mlx->ptr, mlx->wid, mlx->heig);
	mlx->str = (int *)mlx_get_data_addr(mlx->img, &bpp, &s_l, &endian);
	mlx->zoom = 1;
	mlx->move_x = -0.5;
	mlx->move_y = 0;
	mlx->iter = 100;
	mlx->choise_pan = 0;
	mlx->julia.x = -0.835;
	mlx->julia.y = -0.2321;
	mlx->win = mlx_new_window(mlx->ptr, mlx->wid, mlx->heig, title);
	return (mlx);
}

int		ft_usage(void)
{
	ft_putendl("\
usage: ./fractol <fractal name>\
\nfractals: mandelbrot, julia, burningship, tricorn, thunder, bubble, \
shell, feather, cube");
	return (0);
}

int		ft_close(void)
{
	exit(0);
	return (0);
}

int		main(int c, char **v)
{
	t_stock *stock;

	if (c != 2)
		return (ft_usage());
	if (!(stock = (t_stock *)malloc(sizeof(t_stock))))
		return (0);
	if (!(stock->mlx = ft_mlx_setup(v[1])))
		return (0);
	ft_put_fractol_to_img(stock);
	mlx_put_image_to_window(stock->mlx->ptr, stock->mlx->win,\
	stock->mlx->img, 0, 0);
	mlx_hook(stock->mlx->win, 2, (1L << 0), &ft_key, stock);
	mlx_hook(stock->mlx->win, 6, (1L << 6), &ft_mouse_event, stock);
	mlx_hook(stock->mlx->win, 4, (1L << 2), &ft_mouse_zoom, stock);
	mlx_hook(stock->mlx->win, 17, (1L << 17), &ft_close, NULL);
	ft_tutorial(stock);
	mlx_loop(stock->mlx->ptr);
	return (0);
}
