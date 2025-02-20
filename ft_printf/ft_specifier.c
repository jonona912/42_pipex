/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:56:29 by zkhojazo          #+#    #+#             */
/*   Updated: 2024/12/02 18:01:42 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_specifier(const char **s, va_list ap, int *c_ctr)
{
	if (**s == '%' && *(*(s) + 1) == '%')
	{
		if (write(1, *s, 1) < 0)
		{
			return (-1);
		}
		(*c_ctr)++;
		return (1);
	}
	else if (**s == '%' && *(*(s) + 1) != '%')
		return (ft_print_spec(s, ap, c_ctr));
	return (0);
}
