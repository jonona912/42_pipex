/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_free_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:18:06 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/02/20 18:03:57 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int ppx_free_t_args(t_args *p_args)
{
	int i;

	if (!p_args)
		return (0); // Return early if p_args is NULL
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
	free(p_args->limiter);
	free(p_args->here_doc);
	if (p_args->cmds)
	{
		i = 0;
		while (p_args->cmds[i]) // Ensure p_args->cmds is NULL-terminated
		{
			ft_free_double_ptr(p_args->cmds[i]); // Free each command array
			i++;
		}
		free(p_args->cmds); // Free the array of command arrays
		p_args->cmds = NULL;
	}
	return (1);
}
