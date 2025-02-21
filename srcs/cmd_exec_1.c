/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:09:23 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/02/21 23:54:20 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ppx_print_error_cmd(char **cmds)
{
	while (*cmds)
	{
		ft_putstr_fd(*cmds, 2);
		ft_putstr_fd(" ", 2);
		cmds++;
	}
	ft_putstr_fd("\n", 2);
	return (1);
}

int	ppx_command_not_found(char **cmds, char **path)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	ppx_print_error_cmd(cmds);
	free(*path);
	return (0);
}

int infile_pipe(t_pipes pipes, t_args *p_args)
{
	pid_t	p;
	int		fd;
	int		status;
	char    **argv;
	char	*argv2;

	argv2 = "cat";
	argv = {"cat", NULL}; // Arguments for execve
	p = fork();
	if (p == -1) {
		perror("fork");
		return (-1);
	}
	if (p == 0) {
		fd = open(p_args->infile, O_RDONLY);
		if (fd == -1) {
			ft_printf("pipex: %s: %s\n", strerror(errno), p_args->infile);
			exit(EXIT_FAILURE);
		}
		close(pipes.pp1[0]);
		dup2(fd, 0);
		close(fd);
		dup2(pipes.pp1[1], 1);
		close(pipes.pp1[1]);
		execve("/bin/cat", argv, NULL);
	}
	waitpid(p, &status, WNOHANG);
	close(pipes.pp1[1]);
	return (1);
}

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
		perror("Error");
		exit(1);
	}
	// wait(NULL);
	waitpid(p, &status, WNOHANG);
	free(path);
	close(read);
	close(write);
	return (1);
}

int	execute_cmd_struct(t_pipes *pipes, t_args *p_args, int argc)
{
	int	i;
	int	fd;

	i = 0;
	argc -= 5;
	while (i < p_args->cmd_cnt)
	{
		if (i % 2 == 0)
		{
			pipe(pipes->pp2);
			pipes->temp_pp[0] = pipes->pp1[0];
			pipes->temp_pp[1] = pipes->pp2[1];
		}
		else
		{
			pipe(pipes->pp1);
			pipes->temp_pp[0] = pipes->pp2[0];
			pipes->temp_pp[1] = pipes->pp1[1];
		}
		if (i == p_args->cmd_cnt - 1)
		{
			if (p_args->here_doc)
				fd = open(p_args->outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
			else
				fd = open(p_args->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			pipes->temp_pp[1] = fd;
		}
		if (**(p_args->cmds + i))
			execute_cmd(pipes->temp_pp[0], pipes->temp_pp[1], *(p_args->cmds + i), p_args); // you can save a line by i++ in this line
		i++;
	}
	return (i);
}
