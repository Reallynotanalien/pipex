/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:57:05 by kafortin          #+#    #+#             */
/*   Updated: 2023/02/13 16:49:00 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
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
	if (access(argv, F_OK) == 0)
		cmd->path.path = argv;
	else
		cmd->path.path = find_path(cmd, env);
	if (cmd->path.path == NULL)
	{
		free_struct(cmd);
		exit_error("Error: command not found");
	}
	return (cmd);
}

void	child_one(char **argv, int i, t_files *files, char **env)
{
	t_cmd	*cmd;

	printf("I am %i in child_one\n", i);
	cmd = find_cmd(argv[i], env);
	close(files->output);
	close(files->fd[0]);
	dup2(files->fd[1], STDOUT_FILENO);
	close(files->fd[1]);
	execve(cmd->path.path, (char *const *)cmd->cmd, env);
	free_struct(cmd);
}

void	child_two(char **argv, int argc, t_files *files, char **env)
{
	t_cmd	*cmd;

	printf("Yo i'm in child two now\n");
	cmd = find_cmd(argv[argc - 2], env);
	dup2(files->output, STDOUT_FILENO);
	close_all(files);
	execve(cmd->path.path, (char *const *)cmd->cmd, env);
	free_struct(cmd);
}

int	main(int argc, char **argv, char **env)
{
	t_files	files;
	int		i;

	if (argc < 5)
		exit_error("Invalid number of arguments.");
	i = 2;
	open_files(&files, argv, argc);
	dup2(files.input, STDIN_FILENO);
	close(files.input);
	while (i < argc - 2)
	{
		if (pipe(files.fd) < 0)
			exit_error("Error: pipe did not work");
		files.pid1 = fork();
		if (files.pid1 == -1)
			exit_error("Error: fork did not work");
		else if (files.pid1 == 0)
			child_one(argv, i, &files, env);
		else
		{
			close(files.fd[1]);
			dup2(files.fd[0], STDIN_FILENO);
			close(files.fd[0]);
		}
		i++;
	}
	waitpid(files.pid1, NULL, 0);
	child_two(argv, argc, &files, env);
	return (0);
}
