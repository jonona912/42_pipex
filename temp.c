/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:09:23 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/02/21 11:25:34 by zkhojazo         ###   ########.fr       */
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
	return (1);
}

int infile_pipe(int pp[2], t_args *p_args)
{
	pid_t	p;
	int		fd;
	char	*path;

	path = ft_strjoin(p_args->cmd_path, **p_args->cmds);
	if (!path) {
		perror("ft_strjoin");
		return (-1);
	}
	p = fork();
	if (p == -1) {
		perror("fork");
		free(path);
		return (-1);
	}
	if (p == 0) {
		close(pp[0]);
		fd = open(p_args->infile, O_RDONLY);
		if (fd == -1) {
			ft_printf("pipex: %s: %s\n", strerror(errno), p_args->infile);
			free(path);
			exit(EXIT_FAILURE);
		}
		dup2(fd, 0);
		close(fd);
		dup2(pp[1], 1);
		close(pp[1]);
		execve(path, *p_args->cmds, NULL);
		ft_putstr_fd("pipex: command not found: ", 2);
		ppx_print_error_cmd(*p_args->cmds);
		ft_putstr_fd("\n", 2);
		free(path);
		exit(EXIT_FAILURE);
	}
	// wait(NULL);
	int status;
	waitpid(p, &status, WNOHANG);
	close(pp[1]);
	free(path);
	return (1);
}

int	outfile_pipe(int read, t_args *p_args, char **cmd)
{
	pid_t	p;
	int		fd;
	char	*path;

	path = ft_strjoin(p_args->cmd_path, *cmd);
	if (!path)
	{
		perror("path");
		return (0);
	}
	p = fork();
	if (p < 0)
	{
		free(path);
		perror("fork");
		exit(1);
	}
	if (p == 0)
	{
		if (p_args->here_doc)
			fd = open(p_args->outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			fd = open(p_args->outfile, O_CREAT | O_RDWR, 0644);
		if (fd == -1)
		{
			free(path);
			perror("open");
			exit(1);
		}
		dup2(read, 0);
		close(read);
		dup2(fd, 1);
		close(fd);
		execve(path, cmd, NULL);
		perror("execve");
		free(path);
		exit(1);
	}
	wait(NULL);
	free(path);
	close(read);
	return (1);
}

int	execute_cmd(int read, int write, char **cmd, t_args *p_args)
{
	pid_t	p;
	char	*path;

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
	wait(NULL);
	free(path);
	close(read);
	close(write);
	return (1);
}

int	execute_cmd_struct(t_pipes *pipes, t_args *p_args, int argc)
{
	int	i;

	i = 0;
	argc -= 5;
	while (i < argc)
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
		execute_cmd(pipes->temp_pp[0], pipes->temp_pp[1], *(p_args->cmds + i + 1), p_args); // you can save a line by i++ in this line
		i++;
	}
	if (i % 2 == 1)
		pipes->temp_pp[0] = pipes->pp2[0];
	else
		pipes->temp_pp[0] = pipes->pp1[0];
	return (i);
}
