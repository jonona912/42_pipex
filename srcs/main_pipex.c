/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:46:00 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/02/20 20:27:22 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ppx_print_t_args(t_args p_args)
{
	printf("p_args.cmds:\n");
	int	i = 0;
	int	j;
	while (*((p_args.cmds) + i))
	{
		j = 0;
		while (*(*((p_args.cmds) + i) + j))
			printf("%s, ", *(*((p_args.cmds) + i) + j++));
		printf("\n");
		i++;
	}
	printf("\ninfile: %s\n", p_args.infile);
	printf("outfil: %s\n", p_args.outfile);
	printf("hd    : %s\n", p_args.here_doc);
	printf("limite: %s\n", p_args.limiter);
}


// ./pipex here_doc LIMITER cmd cmd1 file
// cmd << LIMITER | cmd1 >> file

int	here_doc_handler(t_pipes pipes, t_args *p_args)
{
	int i;
	pid_t p;

	i = 1;
	p = fork();
	if (p == 0)
	{
		dup2(pipes.pp1[1], 1);
		close(pipes.pp1[1]);
		while (i)
		{
			char *str = get_next_line(0);
			if (!ft_strcmp(str, p_args->limiter))
				break ;
			ft_putstr_fd(str, 1);
		}
		exit (0);
	}
	close(pipes.pp1[1]);
	return (1);
}
int	main(int argc, char **argv)
{
	t_pipes	pipes;
	t_args	p_args;
	int		i;

	p_args.cmd_path = "/bin/";
	if (argc < 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}
	pipe(pipes.pp1);
	ppx_arg_split((argv + 1), &p_args, ' ');
	if (p_args.here_doc)
	{
		argc--;
		here_doc_handler(pipes, &p_args);
	}
	else
		infile_pipe(pipes.pp1, &p_args); // // close pp1[1];
	i = 0;
	pipes.temp_pp[0] = pipes.pp1[0];
	if (argc > 5)
		i = execute_cmd_struct(&pipes, &p_args, argc);
	outfile_pipe(pipes.temp_pp[0], &p_args, *(p_args.cmds + 1 + i)); // closes pp1[0]
	// ft_putstr_fd("end_reached\n", 1);
	ppx_free_t_args(&p_args);
	return (0);
}


// testing cat << END 

// int	main(int argc, char **argv)
// {
// 	int	fd = open("infile", O_RDONLY);
// 	// char *str;

// 	// str =
// }


































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

