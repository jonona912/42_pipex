/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_spec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:03:25 by zkhojazo          #+#    #+#             */
/*   Updated: 2024/12/02 18:13:36 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_numlen(int n)
{
	int	ret;

	ret = 0;
	if (n <= 0)
		ret = 1;
	while (n)
	{
		n /= 10;
		ret++;
	}
	return (ret);
}

static int	ft_print_spec3(const char **s, va_list ap, int *c_ctr)
{
	char	c;
	int		n;

	if (*(*s + 1) == 'c')
	{
		c = ((char)va_arg(ap, int));
		if (write(1, &c, 1) < 0)
		{
			(*c_ctr) = -1;
			return (-1);
		}
		(*c_ctr)++;
		return (1);
	}
	else if (*(*s + 1) == 'u')
	{
		n = (unsigned int) va_arg(ap, unsigned int);
		ft_put_uns_nbr(n, c_ctr);
		if (*c_ctr == -1)
			return (-1);
		(*c_ctr) += ft_pos_numlen(n);
		return (1);
	}
	return (0);
}

static int	ft_print_spec2(const char **s, va_list ap, int *c_ctr)
{
	int		n;

	n = ft_print_spec3(s, ap, c_ctr);
	if (n == -1)
		return (-1);
	else if (n == 1)
		return (1);
	if (*(*s + 1) == 'd' || *(*s + 1) == 'i')
	{
		n = va_arg(ap, int);
		ft_putnbr_ctr(n, c_ctr);
		if (*c_ctr == -1)
			return (-1);
		(*c_ctr) += ft_numlen(n);
		return (1);
	}
	return (0);
}

static int	ft_print_str(const char **s, va_list ap, int *c_ctr)
{
	char	*temp_s;

	if (*(*s + 1) == 's')
	{
		temp_s = va_arg(ap, char *);
		if (!temp_s)
		{
			if (ft_putstr("(null)") < 0)
			{
				(*c_ctr) = -1;
				return (-1);
			}
			(*c_ctr) += 6;
			return (1);
		}
		if (ft_putstr(temp_s) < 0)
		{
			(*c_ctr) = -1;
			return (-1);
		}
		(*c_ctr) += ft_strlen(temp_s);
		return (1);
	}
	return (0);
}

int	ft_print_spec(const char **s, va_list ap, int *c_ctr)
{
	if (ft_print_str(s, ap, c_ctr) > 0)
		return (1);
	else if (ft_print_hexa(s, ap, c_ctr) > 0)
		return (1);
	else if (ft_print_spec2(s, ap, c_ctr) > 0)
		return (1);
	if (*c_ctr == -1)
		return (-1);
	return (0);
}
