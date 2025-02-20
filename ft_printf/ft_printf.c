/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:12:59 by zkhojazo          #+#    #+#             */
/*   Updated: 2024/12/02 15:59:44 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		c_ctr;
	int		flag;

	c_ctr = 0;
	va_start(ap, str);
	while (*str)
	{
		flag = ft_specifier(&str, ap, &c_ctr);
		if (flag == 0)
		{
			if (write (1, str, 1) < 0)
				return (-1);
			str++;
			c_ctr++;
		}
		else if (flag > 0)
			str += 2;
		else
			return (-1);
	}
	va_end(ap);
	return (c_ctr);
}
