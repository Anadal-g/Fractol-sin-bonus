/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:20:35 by anadal-g          #+#    #+#             */
/*   Updated: 2024/04/03 12:59:28 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	julia(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		c->x = fractal->julia_x;
		c->y = fractal->julia_y;
	}
	else
	{
		c->x = z->x;
		c->y = z->y;
	}
}

static void	put_pixel(int x, int y, t_img *img, int color)
{
	int	bytes_per_pixel;
	int	offset;

	if (img == NULL || img->pixels_ptr == NULL)
		return ;
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	bytes_per_pixel = img->bpp / 8;
	if (bytes_per_pixel <= 0 || bytes_per_pixel > 4)
		return ;
	offset = (y * img->line_length) + (x * bytes_per_pixel);
	if (offset < 0 || offset >= img->line_length * HEIGHT)
		return ;
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

static void	handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	z.x = 0.0;
	z.y = 0.0;
	c.x = (map(x, -2, 2, WIDTH));
	c.y = (map(y, 2, -2, HEIGHT));
	while (i < fractal->iter)
	{
		z = suma_num(calc_square(z), c);
		if ((z.x * z.x) + (z.y * z.y) > fractal->escape)
		{
			color = map(i, fractal->color, fractal->color * 10, fractal->iter);
			put_pixel(x, y, &fractal->img, color);
			return ;
		}
		i++;
	}
	put_pixel(x, y, &fractal->img, BLACK);
}

static void	handle_pixel_julia(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	z.x = (map(x, -2, 2, WIDTH));
	z.y = (map(y, 2, -2, HEIGHT));
	julia(&z, &c, fractal);
	while (i < fractal->iter)
	{
		z = suma_num(calc_square(z), c);
		if ((z.x * z.x) + (z.y * z.y) > fractal->escape)
		{
			color = map(i, fractal->color, fractal->color * 6, fractal->iter);
			put_pixel(x, y, &fractal->img, color);
			return ;
		}
		i++;
	}
	put_pixel(x, y, &fractal->img, BLACK);
}

void	fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (!ft_strncmp(fractal->name, "mandelbrot", 10))
			{
				handle_pixel(x, y, fractal);
			}
			else if (!ft_strncmp(fractal->name, "julia", 5))
			{
				handle_pixel_julia(x, y, fractal);
			}
		}
	}
	mlx_put_image_to_window(fractal->mlx_connection, fractal->mlx_window,
		fractal->img.img_ptr, 0, 0);
}
