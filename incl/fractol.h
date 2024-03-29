/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 18:09:06 by tjuana            #+#    #+#             */
/*   Updated: 2019/08/09 16:56:07 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>

# define THREADS 8

typedef struct	s_coord
{
	int			x;
	int			y;
	int			color;
}				t_coord;

typedef struct	s_complex
{
	double		x;
	double		y;
}				t_complex;

typedef struct	s_color
{
	double		r;
	double		g;
	double		b;
	double		f;
	double		p;
	double		q;
	double		t;
	int			i;
}				t_color;

typedef struct	s_mlx
{
	void		*ptr;
	void		*win;
	int			wid;
	int			heig;
	void		*img;
	int			*str;
	int			fractol;
	double		zoom;
	double		move_x;
	double		move_y;
	int			iter;
	int			choise_pan;
	t_coord		*c1;
	t_coord		*c2;
	t_complex	julia;
}				t_mlx;

typedef struct	s_threads
{
	t_mlx		*mlx;
	pthread_t	id;
	int			n;
	int			i;
	int			max;
}				t_threads;

typedef struct	s_stock
{
	t_mlx		*mlx;
}				t_stock;

int				ft_choise(char *file);
t_mlx			*ft_mlx_setup(char *title);
int				ft_usage(void);
int				ft_close(void);
int				main(int c, char **v);
void			ft_put_fractol_to_img(t_stock *stock);
void			ft_fill_pixel(t_mlx *mlx, int x, int y, int color);
int				ft_hsv_to_rgb(double h, double s, double v, int pan);
int				ft_key(int key, t_stock *stock);
void			ft_reset(t_stock *stock);
void			ft_tutorial(t_stock *stock);
void			ft_move(int key, t_stock *stock);
void			ft_zoom_n_iter(int key, t_stock *stock);
void			*ft_mandelbrot(void *threadv);
void			*ft_julia(void *threadv);
void			*ft_tricorn(void *threadv);
void			*ft_thunder(void *threadv);
void			*ft_feather(void *threadv);
void			*ft_shell(void *threadv);
void			*ft_bubble(void *threadv);
void			*ft_burning_ship(void *threadv);
void			*ft_cube(void *threadv);
int				ft_mouse_event(int x, int y, t_stock *stock);
int				ft_mouse_zoom(int key, int x, int y, t_stock *stock);

#endif
