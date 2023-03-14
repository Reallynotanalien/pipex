/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:05:02 by kafortin          #+#    #+#             */
/*   Updated: 2023/03/14 17:13:49 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	open_errors(t_files *files)
{
	if (files->input < 0)
	{
		close(files->output);
		exit_error(OPEN_ERROR);
	}
	if (files->output < 0)
	{
		close(files->input);
		exit_error(OPEN_ERROR);
	}
}

/*Frees the whole cmd struct properly.*/
void	free_struct(t_cmd *cmd)
{
	if (cmd->path.path)
		free(cmd->path.path);
	free_tab(cmd->path.paths);
	free_tab(cmd->cmd);
	if (cmd)
		free(cmd);
}

/*Close all open files.*/
void	close_all(t_files *files)
{
	close(files->fd[0]);
	close(files->fd[1]);
	close(files->output);
}

/*Exits the program and prints the error message sent as an argument.*/
void	exit_error(char *error)
{
	perror(error);
	exit(1);
}

/*Close all open files and exits.*/
void	close_exit(char *error, t_files *files)
{
	close_all(files);
	exit_error(error);
}
