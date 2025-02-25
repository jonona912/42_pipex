/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec_1_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:09:23 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/02/22 15:29:18 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	execute_cmd(int read, int write, char **cmd, t_args *p_args)
{
	pid_t	p;
	char	*path;
	int		status;

	path = ft_strjoin(p_args->cmd_path, *cmd);
	p = fork();
	if (p == 0)
	{
		dup2(write, 1);
		close(write);
		dup2(read, 0);
		close(read);
		execve(path, cmd, NULL);
		ppx_print_error_cmd(cmd);
		ft_putstr_fd("command not found\n", 2);
		ppx_free_t_args(p_args);
		free(path);
		exit(1);
	}
	waitpid(p, &status, WNOHANG);
	free(path);
	close(read);
	close(write);
	return (1);
}

int	set_pipes(t_pipes *pipes, int is_pp1)
{
	if (is_pp1)
	{
		pipe(pipes->pp1);
		pipes->temp_pp[0] = pipes->pp2[0];
		pipes->temp_pp[1] = pipes->pp1[1];
	}
	else
	{
		pipe(pipes->pp2);
		pipes->temp_pp[0] = pipes->pp1[0];
		pipes->temp_pp[1] = pipes->pp2[1];
	}
	return (1);
}

void	execute_cmd_struct(t_pipes *pipes, t_args *p_args)
{
	int	i;
	int	fd;

	i = 0;
	while (i < p_args->cmd_cnt)
	{
		if (i % 2 == 0)
			set_pipes(pipes, 0);
		else
			set_pipes(pipes, 1);
		if (i == p_args->cmd_cnt - 1)
		{
			if (p_args->here_doc)
				fd = open(p_args->outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
			else
				fd = open(p_args->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				ppx_print_error(p_args, p_args->outfile);
			pipes->temp_pp[1] = fd;
		}
		if (**(p_args->cmds + i))
			execute_cmd(pipes->temp_pp[0], pipes->temp_pp[1],
				*(p_args->cmds + i), p_args);
		i++;
	}
}
