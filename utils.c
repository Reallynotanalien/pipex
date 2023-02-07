/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:05:02 by kafortin          #+#    #+#             */
/*   Updated: 2023/01/18 18:47:06 by kafortin         ###   ########.fr       */
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

void	exit_error(char *error)
{
	perror(error);
	exit(1);
}

void	close_all(t_files *files)
{
	close(files->fd[0]);
	close(files->fd[1]);
	close(files->input);
	close(files->output);
}

void	open_files(t_files *files, char **argv)
{
	files->input = open(argv[1], O_RDONLY);
	if (files->input < 0)
		exit_error("Error: file could not be opened");
	files->output = open(argv[4], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (files->output < 0)
		exit_error("Error: file could not be opened/created");
}
