/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_escale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:04:15 by anadal-g          #+#    #+#             */
/*   Updated: 2024/04/03 13:00:25 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

double	map(double uns_num, double new_min, double new_max, double old_max)
{
	return ((new_max - new_min) * (uns_num - 0) / (old_max - 0) + new_min);
}

t_complex	suma_num(t_complex z1, t_complex z2)
{
	t_complex	result;

	result.x = z1.x + z2.x;
	result.y = z1.y + z2.y;
	return (result);
}

t_complex	calc_square(t_complex z)
{
	t_complex	result;

	result.x = (z.x * z.x) - (z.y * z.y);
	result.y = 2 * z.x * z.y;
	return (result);
}

static double	ft_atodbl2(char *str, double nb)
{
	double	dec;
	double	aux;

	dec = 10;
	while (*str >= '0' && *str <= '9')
	{
		nb = ((*str - '0') + (nb * 10));
		str++;
	}
	if (*str == '.')
	{
		dec = 10;
		str++;
		while (*str >= '0' && *str <= '9')
		{
			aux = ((*str - '0'));
			nb = nb + (aux / dec);
			dec *= 10;
			str++;
		}
	}
	return (nb);
}

double	ft_atodbl(char *str, t_fractal *fractal)
{
	double	nb;
	int		sing;

	nb = 0;
	sing = 0;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sing = 1;
		str++;
	}
	nb = ft_atodbl2(str, nb);
	if (*str < '0' || *str > '9')
		fractal->error = 1;
	if (sing == 1)
		nb = nb * -1;
	return (nb);
}
