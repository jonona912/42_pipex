/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:29:29 by zkhojazo          #+#    #+#             */
/*   Updated: 2024/12/01 13:37:02 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include "../libft/libft.h"

int		ft_printf(const char *str, ...);
int		ft_specifier(const char **s, va_list ap, int *c_ctr);
int		ft_print_spec(const char **s, va_list ap, int *c_ctr);
void	ft_put_uns_nbr(unsigned int n, int *c_ctr);
int		ft_print_hexa(const char **s, va_list ap, int *c_ctr);
void	ft_put_nbr_base(uintptr_t	num, char *base, int *c_ctr);
int		ft_putstr(char *s);
void	ft_putnbr_ctr(int n, int *c_ctr);
int		ft_pos_numlen(unsigned int n);

#endif
