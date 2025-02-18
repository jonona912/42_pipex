/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:46:00 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/02/18 19:01:42 by zkhojazo         ###   ########.fr       */
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

int	ppx_arg_split(char **argv, t_args *p_args, char c)
{
	// char	***ret;
	int		arg_len;
	int		i;

	arg_len = ppx_arg_len(argv);
	p_args->cmds = (char ***)malloc(sizeof(char *) * (arg_len - 1));
	if (!p_args->cmds) // exit with printing error
		return (0);
	p_args->infile = ft_strdup(*argv);
	i = 1;
	while (*(argv + i + 1))
	{
		*(p_args->cmds + i - 1) = ft_split(*(argv + i), c);
		if(!*(p_args->cmds + i - 1))
		{
			perror("Malloc Error:");
			exit(1);
		}
		i++;
	}
	*(p_args->cmds + i) = NULL;
	p_args->outfile = ft_strdup(*(argv + i));
	return (1);
}

void	ppx_print_t_args(t_args p_args)
{
	printf("p_args.cmds:\n");
	int	i = 0;
	int	j;
	while (*((p_args.cmds) + i))
	{
		j = 0;
		while (*(*((p_args.cmds) + i) + j))
			printf("%s ", *(*((p_args.cmds) + i) + j++));
		printf("\n");
		i++;
	}
	printf("infile: %s\n", p_args.infile);
	printf("outfile: %s\n", p_args.outfile);
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
			perror("open");
			free(path);
			exit(EXIT_FAILURE);
		}
		dup2(fd, 0);
		close(fd);
		dup2(pp[1], 1);
		close(pp[1]);
		execve(path, *p_args->cmds, NULL);
		perror("execve");  // If execve fails
		free(path);
		exit(EXIT_FAILURE);
	}
	wait(NULL);
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

int	main(int argc, char **argv)
{
	int		pp1[2];
	int		pp2[2];
	int		temp_pp[2];
	t_args	p_args;

	p_args.cmd_path = "/bin/";
	if (argc < 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}
	pipe(pp1);
	ppx_arg_split((argv + 1), &p_args, ' ');
	infile_pipe(pp1, &p_args);// // close pp1[1];
	// pipe(pp2) if i is odd
	// pipe(pp1) if i is even
	// pp[0] = pp1[0];
	// pp[1] = pp2[1]
	// int pp[2];
	// pp2[2] -- pipe(pp2) --> read from pp1[0] and write to pp2[1] // not pp1 is free
	// pp3[2] -- pipe(pp1) --> read from pp2[0] and wrtie to pp1[1] // pp1[1] not freed
	// pp4[2] -- pipe(pp2) --> read from pp1[0] and write to pp2[1]
	int	i;
	i = 0;
	temp_pp[0] = pp1[0];
	if (argc > 5)
	{
		argc -= 5;
		while (i < argc)
		{
			if (i % 2 == 0)
			{
				pipe(pp2);
				temp_pp[0] = pp1[0];
				temp_pp[1] = pp2[1];
			}
			else
			{
				pipe(pp1);
				temp_pp[0] = pp2[0];
				temp_pp[1] = pp1[1];
			}
			execute_cmd(temp_pp[0], temp_pp[1], *(p_args.cmds + i + 1), &p_args);
			temp_pp[0] = pp2[0];
			i++;
		}
	}
	outfile_pipe(temp_pp[0], &p_args, *(p_args.cmds + 1 + i)); // closes pp1[0]
	ft_putstr_fd("end_reached\n", 1);
	return (0);
}







































// char	***ppx_arg_split(char **argv, char c)
// {
// 	char	***ret;
// 	int		arg_len;
// 	int		i;

// 	arg_len = ppx_arg_len(argv);
// 	ret = (char ***)malloc(sizeof(char *) * (arg_len + 1));
// 	if (!ret)
// 		return (NULL);
// 	i = 0;
// 	while (i < arg_len)
// 	{
// 		*(ret + i) = ft_split(*(argv + i), c);
// 		if(!*(ret + i))
// 		{
// 			perror("Malloc Error:");
// 			exit(1);
// 		}
// 		i++;
// 	}
// 	*(ret + i) = NULL;
// 	return (ret);
// }


// int	main(int argc, char **argv)
// {
// 	// char	***cmds;
// 	char	*path;
// 	int		fd;
// 	int		pp1[2];
// 	t_args	p_args;

// 	if (argc < 2)
// 	{
// 		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
// 		return (1);
// 	}
// 	pipe(pp1);
// 	p_args.cmds = ppx_arg_split((argv + 2), ' ');
// 	path = ft_strjoin("/bin/", *(*p_args.cmds));
// 	pid_t	p;
// 	p = fork(); // handle error
// 	if (p == 0)
// 	{
// 		fd = open(*(argv + 1), O_RDONLY);
// 		dup2(fd, 0);
// 		close(fd);
// 		dup2(pp1[1], 1);
// 		close(pp1[1]);
// 		execve(path, *(p_args.cmds), NULL);
// 	}
// 	wait(NULL);
// 	close(pp1[1]);
// 	p = fork();
// 	if (p == 0)
// 	{
// 		fd = open("outfileasdf", O_CREAT | O_RDWR, 0644);
// 		// close(pp1[1]);
// 		dup2(pp1[0], 0);
// 		close(pp1[0]);
// 		dup2(fd, 1);
// 		close(fd);
// 		path = ft_strjoin("/bin/", **(p_args.cmds + 1));
// 		if (execve(path, *(p_args.cmds + 1), NULL) == -1)
// 		{
// 			perror("execve: ");
// 			exit(1);
// 		}
// 	}
// 	wait(NULL);
// 	printf("lajksd;f\n");
// 	return (0);
// }

