/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:57:05 by kafortin          #+#    #+#             */
/*   Updated: 2023/02/21 18:37:16 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>

void	child_one(char **argv, int i, t_files *files, char **env)
{
	t_cmd	*cmd;

	cmd = find_cmd(argv[i], env);
	close(files->fd[0]);
	close (files->output);
	dup2(files->fd[1], STDOUT_FILENO);
	close(files->fd[1]);
	execve(cmd->path.path, (char *const *)cmd->cmd, env);
	free_struct(cmd);
}

void	child_two(char **argv, int argc, t_files *files, char **env)
{
	t_cmd	*cmd;

	if (pipe(files->fd) < 0)
		exit_error("Error: pipe did not work");
	files->pid1 = fork();
	if (files->pid1 == -1)
		exit_error("Error: fork did not work");
	else if (files->pid1 == 0)
	{
		cmd = find_cmd(argv[argc - 2], env);
		dup2(files->output, STDOUT_FILENO);
		execve(cmd->path.path, (char *const *)cmd->cmd, env);
		free_struct(cmd);
	}
}

void	command_loop(int argc, char **argv, char **env, t_files *files)
{
	int	i;

	i = 2;
	if (ft_strncmp("here_doc", argv[1], 8) == 0)
		i = 3;
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

void	validate_heredoc(char **argv, int argc, t_files *files)
{
	char	*str;

	if (ft_strncmp("here_doc", argv[1], 8) == 0)
	{
		if (argc < 6)
			exit_error("Invalid number of arguments.");
		files->input = open(".here_doc", O_TRUNC | O_CREAT | O_RDWR);
		while (get_next_line(0, &str))
		{
			if ((ft_strlen(str) == ft_strlen(argv[2]) + 1)
				&& (ft_strncmp(str, argv[2], ft_strlen(argv[2])) == 0))
				break ;
			else
				write(files->input, str, ft_strlen(str));
		}
	}
	else
	{
		files->input = open(argv[1], O_RDONLY);
		if (files->input < 0)
			exit_error("Error: file could not be opened");
	}
}

int	main(int argc, char **argv, char **env)
{
	t_files	files;

	if (argc < 5)
		exit_error("Invalid number of arguments.");
	validate_heredoc(argv, argc, &files);
	files.output = open(argv[argc - 1], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (files.output < 0)
		exit_error("Error: file could not be opened/created");
	dup2(files.input, STDIN_FILENO);
	close(files.input);
	command_loop(argc, argv, env, &files);
	if (ft_strncmp("here_doc", argv[1], 8) == 0)
		unlink("./.here_doc");
	child_two(argv, argc, &files, env);
	waitpid(files.pid1, NULL, 0);
	return (0);
}
