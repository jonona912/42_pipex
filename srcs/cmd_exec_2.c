/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:07:48 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/02/22 15:25:31 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// int	ppx_print_error_cmd(char **cmds)
// {
// 	while (*cmds)
// 	{
// 		ft_putstr_fd(*cmds, 2);
// 		ft_putstr_fd(" ", 2);
// 		cmds++;
// 	}
// 	ft_putstr_fd(":", 2);
// 	return (1);
// }

// int	ppx_command_not_found(char **cmds, char **path)
// {
// 	ft_putstr_fd("pipex: command not found: ", 2);
// 	ppx_print_error_cmd(cmds);
// 	free(*path);
// 	return (0);
// }

char	**make_cat_argv(char *str)
{
	char	**ret;

	ret = (char **)malloc(sizeof(char *) * 2);
	if (!ret)
		return (NULL);
	*ret = ft_strdup(str);
	*(ret + 1) = NULL;
	return (ret);
}

int	infile_pipe_helper(t_pipes pipes, t_args *p_args, char ***cat)
{
	int	fd;

	fd = open(p_args->infile, O_RDONLY);
	if (fd == -1)
	{
		free(**cat);
		free(*cat);
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(p_args->infile, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		ppx_free_t_args(p_args);
		exit(EXIT_FAILURE);
	}
	close(pipes.pp1[0]);
	dup2(fd, 0);
	close(fd);
	dup2(pipes.pp1[1], 1);
	close(pipes.pp1[1]);
	execve("/bin/cat", *cat, NULL);
	return (1);
}

int	infile_pipe(t_pipes pipes, t_args *p_args)
{
	pid_t	p;
	int		status;
	char	**cat;

	cat = make_cat_argv("cat");
	if (!cat)
		ppx_free_perror(p_args, "malloc");
	p = fork();
	if (p == -1)
		ppx_free_perror(p_args, "fork");
	if (p == 0)
		infile_pipe_helper(pipes, p_args, &cat);
	waitpid(p, &status, WNOHANG);
	close(pipes.pp1[1]);
	free(*cat);
	free(cat);
	return (1);
}
