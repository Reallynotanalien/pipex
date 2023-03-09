/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:05:22 by kafortin          #+#    #+#             */
/*   Updated: 2023/03/08 19:52:15 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <signal.h>
#include <stdbool.h>

int	find_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			break ;
		i++;
		if (env[i + 1] == NULL)
			exit_error(ENV_ERROR);
	}
	return (i);
}

char	*find_path(t_cmd *cmd, char **env)
{
	int		i;

	i = find_env(env);
	cmd->path.paths = (char **)ft_split(env[i], ':');
	i = 0;
	while (cmd->path.paths[i])
	{
		i++;
		cmd->path.part = ft_strjoin(cmd->path.paths[i], "/");
		cmd->path.path = ft_strjoin (cmd->path.part, cmd->cmd[0]);
		if (cmd->path.part != NULL)
			free(cmd->path.part);
		if (access(cmd->path.path, F_OK) == 0)
			return (cmd->path.path);
		free(cmd->path.path);
		cmd->path.path = NULL;
	}
	return (NULL);
}

t_cmd	*find_cmd(char *argv, char **env)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	cmd->cmd = (char **)ft_split(argv, ' ');
	if (cmd->cmd == NULL)
	{
		free_struct(cmd);
		exit_error(COMMAND_ERROR);
	}
	if (access(argv, F_OK) == 0)
		cmd->path.path = argv;
	else
		cmd->path.path = find_path(cmd, env);
	if (cmd->path.path == NULL)
	{
		free_struct(cmd);
		exit_error(COMMAND_ERROR);
	}
	return (cmd);
}
