/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:46:00 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/02/16 21:49:04 by zkhojazo         ###   ########.fr       */
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

char	***ppx_arg_split(char **argv, char c)
{
	char	***ret;
	int		arg_len;
	int		i;

	arg_len = ppx_arg_len(argv);
	ret = (char ***)malloc(sizeof(char *) * (arg_len + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < arg_len)
	{
		*(ret + i) = ft_split(*(argv + i), c);
		if(!*(ret + i))
		{
			perror("Malloc Error:");
			exit(1);
		}
		i++;
	}
	*(ret + i) = NULL;
	return (ret);
}

int	main(int argc, char **argv)
{
	char	***cmds;
	char	*path;
	char	*infile;

	if (argc < 2)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}
	infile = *(argv + 1);
	cmds = ppx_arg_split((argv + 1), ' ');
	path = ft_strjoin("/bin/", *(*cmds));
	pid_t	p;
	p = fork(); // handle error
	if (p == 0)
		execve(path, *(cmds), NULL);
	else 
		wait(NULL);
	printf("REACHED\n");
	return (0);
}







