/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipex_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:46:00 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/02/22 15:29:24 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

// void	ppx_print_t_args(t_args p_args)
// {
// 	printf("p_args.cmds:\n");
// 	int	i = 0;
// 	int	j;
// 	while (*((p_args.cmds) + i))
// 	{
// 		j = 0;
// 		while (*(*((p_args.cmds) + i) + j))
// 			printf("%s, ", *(*((p_args.cmds) + i) + j++));
// 		printf("\n");
// 		i++;
// 	}
// 	printf("\ninfile: %s\n", p_args.infile);
// 	printf("outfil: %s\n", p_args.outfile);
// 	printf("hd    : %s\n", p_args.here_doc);
// 	printf("limite: %s\n", p_args.limiter);
// }

int	get_user_inputs(t_args *p_args)
{
	char	*str;

	while (1)
	{
		str = get_next_line(0);
		if (!ft_strcmp(str, p_args->limiter))
		{
			free(str);
			break ;
		}
		ft_putstr_fd(str, 1);
		free(str);
	}
	return (1);
}

int	here_doc_handler(t_pipes pipes, t_args *p_args)
{
	pid_t	p;

	p = fork();
	if (p == -1)
		ppx_free_perror(p_args, "fork");
	if (p == 0)
	{
		dup2(pipes.pp1[1], 1);
		close(pipes.pp1[1]);
		get_user_inputs(p_args);
		ppx_free_t_args(p_args);
		exit (0);
	}
	wait(NULL);
	close(pipes.pp1[1]);
	return (1);
}

int	p_args_init(t_args *p_args)
{
	if (!p_args)
		return (0);
	p_args->cmds = NULL;
	p_args->here_doc = NULL;
	p_args->limiter = NULL;
	p_args->infile = NULL;
	p_args->outfile = NULL;
	p_args->cmd_path = "/bin/";
	p_args->cmd_cnt = 0;
	return (1);
}

int	main(int argc, char **argv)
{
	t_pipes	pipes;
	t_args	p_args;

	p_args_init(&p_args);
	if (argc < 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}
	ppx_arg_split((argv + 1), &p_args, ' ');
	pipe(pipes.pp1);
	if (p_args.here_doc)
		here_doc_handler(pipes, &p_args);
	else
		infile_pipe(pipes, &p_args);
	execute_cmd_struct(&pipes, &p_args);
	ppx_free_t_args(&p_args);
	return (0);
}
