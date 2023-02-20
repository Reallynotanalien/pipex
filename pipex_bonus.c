/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:57:05 by kafortin          #+#    #+#             */
/*   Updated: 2023/02/20 16:39:22 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <signal.h>
#include <stdbool.h>

void	child_one(char **argv, int i, t_files *files, char **env)
{
	t_cmd	*cmd;

	cmd = find_cmd(argv[i], env);
	close(files->fd[0]);
	dup2(files->fd[1], STDOUT_FILENO);
	close(files->fd[1]);
	execve(cmd->path.path, (char *const *)cmd->cmd, env);
	free_struct(cmd);
}

void	child_two(char **argv, int argc, t_files *files, char **env)
{
	t_cmd	*cmd;

	cmd = find_cmd(argv[argc - 2], env);
	files->output = open(argv[argc - 1], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (files->output < 0)
		exit_error("Error: file could not be opened/created");
	dup2(files->output, STDOUT_FILENO);
	execve(cmd->path.path, (char *const *)cmd->cmd, env);
	free_struct(cmd);
}

void	command_loop(int argc, char **argv, char **env, t_files *files)
{
	int	i;

	i = 2;
	while (i < argc - 2)
	{
		if (pipe(files->fd) < 0)
			exit_error("Error: pipe did not work");
		files->pid1 = fork();
		if (files->pid1 == -1)
			exit_error("Error: fork did not work");
		else if (files->pid1 == 0)
			child_one(argv, i, files, env);
		else
		{
			close(files->fd[1]);
			dup2(files->fd[0], STDIN_FILENO);
			close(files->fd[0]);
		}
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_files	files;

	if (argc < 5)
		exit_error("Invalid number of arguments.");
	files.input = open(argv[1], O_RDONLY);
	if (files.input < 0)
		exit_error("Error: file could not be opened");
	dup2(files.input, STDIN_FILENO);
	close(files.input);
	command_loop(argc, argv, env, &files);
	child_two(argv, argc, &files, env);
	waitpid(files.pid1, NULL, 0);
	return (0);
}
