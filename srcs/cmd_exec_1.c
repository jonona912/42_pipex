/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:09:23 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/02/21 12:19:54 by zkhojazo         ###   ########.fr       */
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
	fd = open(p_args->infile, O_RDONLY);
	if (fd == -1) {
		ft_printf("pipex: %s: %s\n", strerror(errno), p_args->infile);
		free(path);
		exit(EXIT_FAILURE);
	}
	p = fork();
	if (p == -1) {
		perror("fork");
		free(path);
		return (-1);
	}
	// ft_putstr_fd("erjaf;ldj\n", 2);
	if (p == 0) {
		close(pp[0]);
		// fd = open(p_args->infile, O_RDONLY);
		// if (fd == -1) {
		// 	ft_printf("pipex: %s: %s\n", strerror(errno), p_args->infile);
		// 	free(path);
		// 	exit(EXIT_FAILURE);
		// }
		dup2(fd, 0);
		close(fd);
		dup2(pp[1], 1);
		close(pp[1]);
		execve(path, *p_args->cmds, NULL);
		ft_putstr_fd("pipex: command not found: ", 2);
		ppx_print_error_cmd(*p_args->cmds);
		// ft_putstr_fd("\n", 2);
		// perror("pipex:"); 
		// ft_putstr_fd("pipex: ", 2);
		// ft_putstr_fd(strerror(errno), 2);
		// ft_putstr_fd(": ", 2);
		// ft_putstr_fd(**p_args->cmds, 2);
		// ft_putstr_fd("\n", 2);
		// ft_printf("pipex: command not found: %s\n", p_args->infile);
		free(path);
		exit(EXIT_FAILURE);
	}
	wait(NULL);
	int status;
	waitpid(p, &status, WNOHANG);
	close(fd);
	// if (waitpid(p, &status, WNOHANG) == 0) {
	// 	// Child process has not finished yet
	// 	printf("No data available yet.\n");
	// }
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
			ft_printf("pipex: %s: %s\n", strerror(errno), p_args->outfile);
			free(path);
			exit(EXIT_FAILURE);
		}
		dup2(read, 0);
		close(read);
		dup2(fd, 1);
		close(fd);
		execve(path, cmd, NULL);
		ppx_command_not_found(*p_args->cmds, &path);
		// perror("execve");
		// ft_putstr_fd("pipex: command not found: ", 2);
		// ppx_print_error_cmd(*p_args->cmds);
		// ft_putstr_fd("\n", 2);
		// free(path);
		exit(1);
	}
	// wait(NULL);
	int status;
	waitpid(p, &status, WNOHANG);
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
	// wait(NULL);
	int	status;
	waitpid(p, &status, WNOHANG);
	// if (waitpid(p, &status, WNOHANG) == 0) {
	// 	// Child process has not finished yet
	// 	printf("No data available yet.\n");
	// }
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
