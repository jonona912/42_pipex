/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_ctr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:01:06 by zkhojazo          #+#    #+#             */
/*   Updated: 2024/12/02 18:13:58 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_ctr(int n, int *c_ctr)
{
	long long	i;
	int			c;

	i = n;
	if (i < 0)
	{
		c = '-';
		if (write(1, &c, 1) < 0)
		{
			*c_ctr = -1;
			return ;
		}
		i *= (-1);
	}
	if (i > 9)
		ft_putnbr_ctr(i / 10, c_ctr);
	c = ((i % 10) + '0');
	if (write(1, &c, 1) < 0)
	{
		*c_ctr = -1;
		return ;
	}
}
