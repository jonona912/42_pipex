/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_errors_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:45:27 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/02/22 15:29:27 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	ppx_print_error_cmd(char **cmds)
{
	while (*cmds)
	{
		ft_putstr_fd(*cmds, 2);
		ft_putstr_fd(" ", 2);
		cmds++;
	}
	ft_putstr_fd(":", 2);
	return (1);
}

int	ppx_command_not_found(char **cmds, char **path)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	ppx_print_error_cmd(cmds);
	free(*path);
	return (0);
}

void	ppx_free_perror(t_args *p_args, char *str)
{
	ppx_free_t_args(p_args);
	perror(str);
	exit(1);
}

void	ppx_print_error(t_args *p_args, char *str)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	ppx_free_t_args(p_args);
	exit(1);
}
