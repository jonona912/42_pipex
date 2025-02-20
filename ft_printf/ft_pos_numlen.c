/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pos_numlen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:05:30 by zkhojazo          #+#    #+#             */
/*   Updated: 2024/12/02 18:05:55 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pos_numlen(unsigned int n)
{
	int	ret;

	ret = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / 10;
		ret++;
	}
	return (ret);
}
