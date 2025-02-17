/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:46:00 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/02/17 23:53:24 by zkhojazo         ###   ########.fr       */
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
	p_args->cmds = (char ***)malloc(sizeof(char *) * (arg_len + 1));
	if (!p_args->cmds) // exit with printing error
		return (0);
	p_args->infile = ft_strdup(*argv);
	i = 1;
	while (*(argv + i + 1))
	{
		*(p_args->cmds + i) = ft_split(*(argv + i), c);
		if(!*(p_args->cmds + i))
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

int	main(int argc, char **argv)
{
	// char	***cmds;
	// char	*path;
	// int		fd;
	int		pp1[2];
	t_args	p_args;

	if (argc < 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}
	pipe(pp1);
	ppx_arg_split((argv + 1), &p_args, ' ');
	ppx_print_t_args(p_args);
	// path = ft_strjoin("/bin/", *(*p_args.cmds));
	// pid_t	p;
	// p = fork(); // handle error
	// if (p == 0)
	// {
	// 	fd = open(*(argv + 1), O_RDONLY);
	// 	dup2(fd, 0);
	// 	close(fd);
	// 	dup2(pp1[1], 1);
	// 	close(pp1[1]);
	// 	execve(path, *(p_args.cmds), NULL);
	// }
	// wait(NULL);
	// close(pp1[1]);
	// p = fork();
	// if (p == 0)
	// {
	// 	fd = open("outfileasdf", O_CREAT | O_RDWR, 0644);
	// 	// close(pp1[1]);
	// 	dup2(pp1[0], 0);
	// 	close(pp1[0]);
	// 	dup2(fd, 1);
	// 	close(fd);
	// 	path = ft_strjoin("/bin/", **(p_args.cmds + 1));
	// 	if (execve(path, *(p_args.cmds + 1), NULL) == -1)
	// 	{
	// 		perror("execve: ");
	// 		exit(1);
	// 	}
	// }
	// wait(NULL);
	// printf("lajksd;f\n");
	// return (0);
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

