/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:16:58 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/02/20 17:58:59 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int		ppx_arg_len(char **argv)
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

char	**ppx_split(char const *s, char c, char *c_ignores)
{
	size_t	params;
	char	**ret;
	size_t		i;
	size_t	word_len;

	params = count_cmd_param(s, c, c_ignores);
	// printf("str: %s params: %zu\n", s, params);
	ret = (char **)malloc(sizeof(char *) * (params + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (*s && i < params)
	{
		word_len = ppx_word_len(s, c, c_ignores);
		*(ret + i) = (char *)malloc(sizeof(char *) * (word_len + 1));
		if (!*(ret + i))
		{
			// free memory
			return (NULL);
		}
		if (ft_strchr(c_ignores, *s))
			s++;
		ft_strlcpy(*(ret + i), s, word_len + 1);
		s += word_len;
		if (ft_strchr(c_ignores, *s))
			s++;
		while (*s && *s == c)
			s++;
		i++;
	}
	*(ret + i) = NULL;
	return (ret);
}

int	ppx_arg_split(char **argv, t_args *p_args, char c)
{
	int		cmd_len;
	int		i;

	if (!ft_strcmp(*argv, "here_doc"))
	{
		p_args->here_doc = ft_strdup(*argv);
		argv++;
		if (!p_args->here_doc)
			exit (10);
		p_args->infile = NULL;

		p_args->limiter = ft_strjoin(*argv, "\n"); //ft_strdup(*(++argv));
		if (!p_args->limiter)
			exit (11);
		argv++;
	}
	else
	{
		p_args->here_doc = NULL;
		p_args->infile = ft_strdup(*argv);
		if (!p_args->infile)
			return (0);
		argv++;
		p_args->limiter = NULL;
	}
	cmd_len = ppx_arg_len(argv) - 1; // -2 because of outfile
	// cmd_len -= 1; 
	// printf("arg_len: %d\n", arg_len);
	p_args->cmds = (char ***)malloc(sizeof(char *) * (cmd_len + 1));
	if (!p_args->cmds) // exit with printing error
		return (0);
	// p_args->infile = ft_strdup(*argv);
	i = 0;
	// argv++;
	while (i < cmd_len)
	{
		*(p_args->cmds + i) = ppx_split(*(argv + i), c, "'\""); // ft_split(*(argv + i), c);
		// ppx_split(*(argv + i), c, "'\"");
		if(!*(p_args->cmds + i))
		{
			perror("Malloc Error:"); // free memory
			exit(1);
		}
		i++;
	}
	*(p_args->cmds + i) = NULL;
	p_args->outfile = ft_strdup(*(argv + i));
	return (1);
}
