/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:05:02 by kafortin          #+#    #+#             */
/*   Updated: 2023/03/08 19:59:08 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	close_all(t_files *files)
{
	close(files->fd[0]);
	close(files->fd[1]);
	close(files->input);
	close(files->output);
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
