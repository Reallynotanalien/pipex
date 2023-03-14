/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:57:05 by kafortin          #+#    #+#             */
/*   Updated: 2023/03/14 17:42:07 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <signal.h>
#include <stdbool.h>

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
	cmd->path.env = (char **)ft_split(env[i] + 5, ':');
	i = 0;
	while (cmd->path.env[i])
	{
		cmd->path.join = ft_strjoin(cmd->path.env[i], "/");
		cmd->path.path = ft_strjoin (cmd->path.join, cmd->cmd[0]);
		free(cmd->path.join);
		if (access(cmd->path.path, F_OK) == 0)
			return (cmd->path.path);
		free(cmd->path.path);
		cmd->path.path = NULL;
		i++;
	}
	return (NULL);
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
		close_all(files);
		exit_error(COMMAND_ERROR);
	}
	if (access(cmd->cmd[0], F_OK) == 0)
		cmd->path.path = cmd->cmd[0];
	else
		cmd->path.path = find_path(cmd, env);
	if (cmd->path.path == NULL
		|| ft_strncmp(ENV_ERROR, cmd->path.path, 43) == 0)
	{
		free_tab(cmd->cmd);
		free_tab(cmd->path.env);
		free(cmd);
		close_all(files);
		exit_error(PATH_ERROR);
	}
	return (cmd);
}

/*Looks for the first command, then executes it.*/
void	child_one(char **argv, t_files *files, char **env)
{
	t_cmd	*cmd;

	cmd = find_cmd(argv[2], env, files);
	dup2(files->fd[1], STDOUT_FILENO);
	dup2(files->input, STDIN_FILENO);
	close_all(files);
	execve(cmd->path.path, (char *const *)cmd->cmd, env);
	free_struct(cmd);
}

/*Looks for the second command, then executes it.*/
void	child_two(char **argv, t_files *files, char **env)
{
	t_cmd	*cmd;

	cmd = find_cmd(argv[3], env, files);
	dup2(files->fd[0], STDIN_FILENO);
	dup2(files->output, STDOUT_FILENO);
	close_all(files);
	execve(cmd->path.path, (char *const *)cmd->cmd, env);
	free_struct(cmd);
}

int	main(int argc, char **argv, char **env)
{
	t_files	files;

	if (argc != 5)
		exit_error(ARG_NUM_ERROR);
	open_files(&files, argv);
	if (pipe(files.fd) < 0)
		exit_error(PIPE_ERROR);
	files.pid1 = fork();
	if (files.pid1 == -1)
		exit_error(FORK_ERROR);
	else if (files.pid1 == 0)
		child_one(argv, &files, env);
	else
	{
		files.pid2 = fork();
		if (files.pid2 == -1)
			exit_error(FORK_ERROR);
		else if (files.pid2 == 0)
			child_two(argv, &files, env);
		close_all(&files);
		waitpid(files.pid1, NULL, 0);
		waitpid(files.pid2, NULL, 0);
	}
	return (0);
}
