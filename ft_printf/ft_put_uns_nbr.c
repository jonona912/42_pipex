/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_uns_nbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:02:39 by zkhojazo          #+#    #+#             */
/*   Updated: 2024/12/02 20:00:01 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_uns_nbr(unsigned int n, int *c_ctr)
{
	unsigned char	c;

	if (n > 9)
		ft_put_uns_nbr(n / 10, c_ctr);
	c = (n % 10 + '0');
	if (write(1, &c, 1) < 0)
	{
		(*c_ctr) = -1;
		return ;
	}
}
