/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:24:01 by zkhojazo          #+#    #+#             */
/*   Updated: 2024/12/02 18:25:19 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_nil(int *c_ctr)
{
	if (ft_putstr("(nil)") < 0)
	{
		*c_ctr = -1;
		return (-1);
	}
	(*c_ctr) += 5;
	return (1);
}

static int	ft_print_void_p(const char **s, va_list ap, int *c_ctr, char *l)
{
	char		c;
	uintptr_t	temp_ptr;

	c = *(*s + 1);
	if (c == 'p')
	{
		temp_ptr = (uintptr_t)(va_arg(ap, void *));
		if (!temp_ptr)
		{
			if (ft_print_nil(c_ctr) == -1)
				return (-1);
			return (1);
		}
		if (ft_putstr("0x") < 0)
		{
			*c_ctr = -1;
			return (-1);
		}
		(*c_ctr) += 2;
		ft_put_nbr_base (temp_ptr, l, c_ctr);
		if (*c_ctr == -1)
			return (-1);
		return (1);
	}
	return (0);
}

int	ft_print_hexa(const char **s, va_list ap, int *c_ctr)
{
	char	c;

	c = *(*s + 1);
	if (c == 'x')
	{
		ft_put_nbr_base(va_arg(ap, unsigned int), "0123456789abcdef", c_ctr);
		if (*c_ctr == -1)
			return (-1);
		return (1);
	}
	else if (c == 'X')
	{
		ft_put_nbr_base(va_arg(ap, unsigned int), "0123456789ABCDEF", c_ctr);
		if (*c_ctr == -1)
			return (-1);
		return (1);
	}
	else if (ft_print_void_p(s, ap, c_ctr, "0123456789abcdef") > 0)
		return (1);
	if (*c_ctr == -1)
		return (-1);
	return (0);
}
