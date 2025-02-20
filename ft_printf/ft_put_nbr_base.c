/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_nbr_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:28:57 by zkhojazo          #+#    #+#             */
/*   Updated: 2024/12/02 13:47:32 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_nbr_base(uintptr_t num, char *base, int *c_ctr)
{
	uintptr_t	base_len;

	base_len = ft_strlen(base);
	if (num > (base_len - 1))
		ft_put_nbr_base(num / base_len, base, c_ctr);
	if (write(1, &base[num % base_len], 1) < 0)
	{
		(*c_ctr) = -1;
		return ;
	}
	(*c_ctr)++;
}
