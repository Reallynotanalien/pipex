/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:05:22 by kafortin          #+#    #+#             */
/*   Updated: 2023/03/13 16:40:11 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <signal.h>
#include <stdbool.h>

char	*access_path(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->path.paths[i])
	{
		cmd->path.part = ft_strjoin(cmd->path.paths[i], "/");
		cmd->path.path = ft_strjoin (cmd->path.part, cmd->cmd[0]);
		free(cmd->path.part);
		if (access(cmd->path.path, F_OK) == 0)
			return (cmd->path.path);
		free(cmd->path.path);
		cmd->path.path = NULL;
		i++;
	}
	return (NULL);
}

/*Looks through the environment to find an executable path for the command sent
as an argument.*/
char	*find_path(t_cmd *cmd, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			break ;
		i++;
		if (env[i] == NULL || env[i + 1] == NULL)
			return (ENV_ERROR);
	}
	cmd->path.paths = (char **)ft_split(env[i] + 5, ':');
	i = 0;
	cmd->path.path = access_path(cmd);
	return (cmd->path.path);
}

/*Takes argv[] as an argument to find what command it is. Checks if absolute
path is executable, if not, finds the right executable path then returns it.*/
t_cmd	*find_cmd(char *argv, char **env, t_files *files)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	cmd->cmd = (char **)ft_split(argv, ' ');
	if (cmd->cmd == NULL)
	{
		free_struct(cmd);
		close_exit(COMMAND_ERROR, files);
	}
	if (access(argv, F_OK) == 0)
		cmd->path.path = argv;
	else
		cmd->path.path = find_path(cmd, env);
	if (cmd->path.path == NULL
		|| ft_strncmp(ENV_ERROR, cmd->path.path, 43) == 0)
	{
		free_struct(cmd);
		close_exit(ENV_ERROR, files);
	}
	return (cmd);
}
