/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_free_mem_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:18:06 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/02/22 15:29:31 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	ppx_free_t_args_hlp(t_args *p_args)
{
	if (p_args->infile)
	{
		free(p_args->infile);
		p_args->infile = NULL;
	}
	if (p_args->outfile)
	{
		free(p_args->outfile);
		p_args->outfile = NULL;
	}
	if (p_args->limiter)
	{
		free(p_args->limiter);
		p_args->limiter = NULL;
	}
	if (p_args->here_doc)
	{
		free(p_args->here_doc);
		p_args->here_doc = NULL;
	}
	return (0);
}

int	ppx_free_t_args(t_args *p_args)
{
	int	i;

	if (!p_args)
		return (0);
	ppx_free_t_args_hlp(p_args);
	if (p_args->cmds)
	{
		i = 0;
		while (*(p_args->cmds + i))
		{
			ft_free_double_ptr(*(p_args->cmds + i));
			i++;
		}
		free(p_args->cmds);
		p_args->cmds = NULL;
	}
	return (1);
}
