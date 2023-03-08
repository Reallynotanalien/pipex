/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:05:02 by kafortin          #+#    #+#             */
/*   Updated: 2023/03/08 16:11:55 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

void	free_struct(t_cmd *cmd)
{
	if (cmd->path.path)
		free(cmd->path.path);
	free_tab(cmd->path.paths);
	free_tab(cmd->cmd);
	if (cmd)
		free(cmd);
}

void	close_all(t_files *files)
{
	close(files->fd[0]);
	close(files->fd[1]);
	close(files->input);
	close(files->output);
}

void	exit_error(char *error)
{
	perror(error);
	exit(1);
}

void	open_files(t_files *files, char **argv)
{
	files->input = open(argv[1], O_RDONLY);
	files->output = open(argv[4], O_TRUNC | O_CREAT | O_WRONLY, 0644);
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
