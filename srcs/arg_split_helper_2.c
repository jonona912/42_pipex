/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split_helper_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 22:08:31 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/02/21 22:34:29 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ppx_split_free(char ***str, int len)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (i < len)
	{
		free((*(*str) + i));
		i++;
	}
	free(*str);
	return (1);
}

char	**ppx_split(char const *s, char c, char *c_ignores)
{
	t_split	vars;

	vars.params = count_cmd_param(s, c, c_ignores);
	vars.ret = (char **)malloc(sizeof(char *) * (vars.params + 1));
	if (!(vars.ret))
		return (NULL);
	vars.i = 0;
	while (*s && vars.i < vars.params)
	{
		vars.wl = ppx_word_len(s, c, c_ignores);
		*(vars.ret + vars.i) = (char *)malloc(sizeof(char *) * (vars.wl + 1));
		if (!*(vars.ret + vars.i))
			return (ppx_split_free(&(vars.ret), vars.i), NULL);
		if (ft_strchr(c_ignores, *s))
			s++;
		ft_strlcpy(*(vars.ret + vars.i), s, vars.wl + 1);
		s += vars.wl;
		if (ft_strchr(c_ignores, *s))
			s++;
		while (*s && *s == c)
			s++;
		(vars.i)++;
	}
	*(vars.ret + vars.i) = NULL;
	return (vars.ret);
}

size_t	ppx_strlen(char const *s, char *c_ignores)
{
	size_t	len;

	len = 0;
	if (*s && ft_strchr(c_ignores, *s))
	{
		s++;
		while (*s && !ft_strchr(c_ignores, *s))
		{
			len++;
			s++;
		}
	}
	else
	{
		while (*s)
		{
			len++;
			s++;
		}
	}
	return (len);
}

char	*ppx_strdup(char *src, char *c_ignores)
{
	size_t	str_len;
	char	*str_ptr;
	char	*temp_ptr;

	str_len = ppx_strlen(src, c_ignores);
	if (!str_len)
		return (NULL);
	str_ptr = malloc(str_len + 1);
	if (!str_ptr)
		return (NULL);
	temp_ptr = str_ptr;
	if (*src && ft_strchr(c_ignores, *src))
		src++;
	while (*src && !ft_strchr(c_ignores, *src))
	{
		*str_ptr = *src;
		str_ptr++;
		src++;
	}
	*str_ptr = '\0';
	return (temp_ptr);
}

int	make_here_doc_str(char ***argv, t_args *p_args)
{
	p_args->here_doc = ppx_strdup(**argv, "'\"");
	if (!p_args->here_doc)
	{
		ft_putstr_fd("pipex: syntax error near unexpected token `|'\n", 2);
		exit (10);
	}
	(*argv)++;
	p_args->limiter = ft_strjoin(**argv, "\n");
	if (!p_args->limiter)
	{
		ppx_free_t_args(p_args);
		exit (11);
	}
	(*argv)++;
	return (1);
}
