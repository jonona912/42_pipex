/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:16:58 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/02/21 23:51:42 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	make_in_out_file( char ***argv, t_args *p_args, int i, t_is_str make)
{
	char	*outfile_error;

	outfile_error = "pipex: syntax error near unexpected token `newline'\n";
	if (make == MK_INFILE)
	{
		p_args->infile = ppx_strdup(**argv, "'\"");
		if (!p_args->infile)
		{
			ppx_free_t_args(p_args);
			ft_putstr_fd("pipex: syntax error near unexpected token `|'\n", 2);
			exit (10);
		}
		(*argv)++;
	}
	else if (make == MK_OUTFILE)
	{
		p_args->outfile = ppx_strdup(*((*argv) + i), "'\"");
		if (!(p_args->outfile))
		{
			ppx_free_t_args(p_args);
			ft_putstr_fd(outfile_error, 2);
			exit (10);
		}
	}
	return (1);
}

void	ppx_free_perror(t_args *p_args, char *str)
{
	ppx_free_t_args(p_args);
	perror(str);
	exit(1);
}

int	ppx_arg_split(char **argv, t_args *p_args, char c)
{
	int	i;

	i = 0;
	if (!ft_strcmp(*argv, "here_doc"))
		make_here_doc_str(&argv, p_args);
	else
		make_in_out_file(&argv, p_args, i, MK_INFILE);
	p_args->cmd_cnt = ppx_arg_len(argv) - 1;
	p_args->cmds = (char ***)malloc(sizeof(char *) * (p_args->cmd_cnt + 1));
	if (!p_args->cmds)
		ppx_free_perror(p_args, "malloc");
	while (i < p_args->cmd_cnt)
	{
		*(p_args->cmds + i) = ppx_split(*(argv + i), c, "'\"");
		if (!*(p_args->cmds + i))
			ppx_free_perror(p_args, "malloc");
		i++;
	}
	*(p_args->cmds + i) = NULL;
	make_in_out_file(&argv, p_args, i, MK_OUTFILE);
	return (1);
}
