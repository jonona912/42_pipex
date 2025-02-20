/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:43:37 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/02/20 18:31:50 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

#include <string.h>  // For strerror
#include <errno.h>   // For errno

# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include "../ft_printf/ft_printf.h"

typedef struct	s_args
{
	char	***cmds;
	char	*here_doc;
	char	*limiter;
	char	*infile;
	char	*outfile;
	char	*cmd_path;
}	t_args;

typedef struct	s_pipes
{
	int	pp1[2];
	int	pp2[2];
	int	temp_pp[2];
} t_pipes;

typedef enum s_hd
{
	NOT_HERE_DOC,
	IS_HERE_DOC
} t_hd;



// cmd_exec_1.c
int infile_pipe(int pp[2], t_args *p_args);
int	outfile_pipe(int read, t_args *p_args, char **cmd);
int	execute_cmd(int read, int write, char **cmd, t_args *p_args);
int	execute_cmd_struct(t_pipes *pipes, t_args *p_args, int argc);

// arg_split.c
int		ppx_arg_len(char **argv);
int	ppx_arg_split(char **argv, t_args *p_args, char c);
char	**ppx_split(char const *s, char c, char *c_ignores);

// ppx_free_meme.c
int ppx_free_t_args(t_args *p_args);

#endif
