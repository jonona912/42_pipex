/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:43:37 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/02/17 23:22:31 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

# include "../libft/libft.h"

typedef struct	s_args
{
	char	***cmds;
	char	*infile;
	char	*outfile;
}	t_args;



#endif
