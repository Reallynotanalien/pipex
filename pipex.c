/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:57:05 by kafortin          #+#    #+#             */
/*   Updated: 2023/02/20 17:22:27 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <signal.h>
#include <stdbool.h>

char	*find_path(t_cmd *cmd, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			break ;
		i++;
		if (env[i + 1] == NULL)
			exit_error("Error: PATH is not an environment variable");
	}
	cmd->path.paths = (char **)ft_split(env[i], ':');
	i = -1;
	while (cmd->path.paths[i++])
	{
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
		exit_error("Error: command not found");
	}
	if (access(cmd->cmd[0], F_OK) == 0)
		cmd->path.path = cmd->cmd[0];
	else
		cmd->path.path = find_path(cmd, env);
	if (cmd->path.path == NULL)
	{
		free_struct(cmd);
		exit_error("Error: command not found");
	}
	return (cmd);
}

void	child_one(char **argv, t_files *files, char **env)
{
	t_cmd	*cmd;

	cmd = find_cmd(argv[2], env);
	dup2(files->fd[1], STDOUT_FILENO);
	dup2(files->input, STDIN_FILENO);
	close_all(files);
	execve(cmd->path.path, (char *const *)cmd->cmd, env);
	free_struct(cmd);
}

void	child_two(char **argv, t_files *files, char **env)
{
	t_cmd	*cmd;

	cmd = find_cmd(argv[3], env);
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
		exit_error("Invalid number of arguments.");
	open_files(&files, argv);
	if (pipe(files.fd) < 0)
		exit_error("Error: pipe did not work");
	files.pid1 = fork();
	if (files.pid1 == -1)
		exit_error("Error: fork did not work");
	else if (files.pid1 == 0)
		child_one(argv, &files, env);
	else
	{
		files.pid2 = fork();
		if (files.pid2 == -1)
			exit_error("Error: fork did not work");
		else if (files.pid2 == 0)
			child_two(argv, &files, env);
		close_all(&files);
		waitpid(files.pid1, NULL, 0);
		waitpid(files.pid2, NULL, 0);
	}
	return (0);
}
