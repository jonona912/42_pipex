/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split_helper_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 22:07:55 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/02/21 22:11:00 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ppx_arg_len(char **argv)
{
	int	i;

	i = 0;
	while (*(argv + i))
		i++;
	return (i);
}

char	*ppx_point_word(char const *s, char c)
{
	if (!s)
		return (NULL);
	while (*s == c)
		s++;
	return ((char *)s);
}

char	*end_of_quote(char const *s, char *c_ignores)
{
	int	flag;

	flag = 1;
	while (*s && flag)
	{
		if (ft_strchr(c_ignores, *s))
			flag = 0;
		s++;
	}
	return ((char *)s);
}

size_t	count_cmd_param(char const *s, char c, char *c_ignores)
{
	size_t	param_ctr;

	param_ctr = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == c)
		{
			param_ctr++;
			s = ppx_point_word(s, c);
		}
		if (ft_strchr(c_ignores, *s))
			s = end_of_quote(++s, c_ignores);
		s++;
	}
	return (param_ctr + 1);
}

size_t	ppx_word_len(char const *s, char c, char *c_ignores)
{
	size_t	len;

	len = 0;
	if (ft_strchr(c_ignores, *s))
	{
		s++;
		while (!ft_strchr(c_ignores, *s))
		{
			len++;
			s++;
		}
	}
	else
	{
		while (*s != c)
		{
			len++;
			s++;
		}
	}
	return (len);
}
