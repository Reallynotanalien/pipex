/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:57:05 by kafortin          #+#    #+#             */
/*   Updated: 2023/03/14 17:04:58 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>

/*Looks for the desired command, then executes it and outputs the
result to the read end of the pipe.*/
void	child_one(char **argv, int i, t_files *files, char **env)
{
	t_cmd	*cmd;

	cmd = find_cmd(argv[i], env, files);
	close(files->fd[0]);
	close(files->output);
	dup2(files->fd[1], STDOUT_FILENO);
	close(files->fd[1]);
	execve(cmd->path.path, (char *const *)cmd->cmd, env);
	free_struct(cmd);
}

/*Creates a new child process for the last command, executes the command and 
redirects the STDOUT_FILENO so it becomes the output file.*/
void	child_two(char **argv, int argc, t_files *files, char **env)
{
	t_cmd	*cmd;

	if (pipe(files->fd) < 0)
		close_exit(PIPE_ERROR, files);
	files->pid = fork();
	if (files->pid == -1)
		close_exit(FORK_ERROR, files);
	else if (files->pid == 0)
	{
		cmd = find_cmd(argv[argc - 2], env, files);
		close(files->fd[0]);
		close(files->fd[1]);
		dup2(files->output, STDOUT_FILENO);
		close(files->output);
		execve(cmd->path.path, (char *const *)cmd->cmd, env);
		free_struct(cmd);
	}
}

/*Creates a new child process for each command (except the last one) and
executes the command in the child.*/
void	command_loop(int argc, char **argv, char **env, t_files *files)
{
	int	i;

	i = 2;
	dup2(files->input, STDIN_FILENO);
	close(files->input);
	if (ft_strncmp("here_doc", argv[1], 8) == 0)
		i = 3;
	while (i < argc - 2)
	{
		if (pipe(files->fd) < 0)
			close_exit(PIPE_ERROR, files);
		files->pid = fork();
		if (files->pid == -1)
			close_exit(FORK_ERROR, files);
		else if (files->pid == 0)
			child_one(argv, i, files, env);
		else
		{
			close(files->fd[1]);
			dup2(files->fd[0], STDIN_FILENO);
			close(files->fd[0]);
		}
		i++;
	}
	child_two(argv, argc, &files, env);
	close_all(&files);
	waitpid(files->pid, NULL, 0);
}

/*Checks to see if the first argument is here_doc. If so, opens a temporary
file and uses get_next_line to take input from the terminal and put it in 
that file. It then becomes the input file. If the first argument is not 
here_doc, the input file (which should be the first arg) is opened.*/
void	open_heredoc(char **argv, int argc, t_files *files)
{
	char	*str;
	int		temp_file;

	if (argc < 6)
		exit_error(ARG_NUM_ERROR);
	temp_file = open(".here_doc", O_TRUNC | O_CREAT | O_WRONLY, 0644);
	while (get_next_line(0, &str))
	{
		if ((ft_strlen(str) == ft_strlen(argv[2]) + 1)
			&& (ft_strncmp(str, argv[2], ft_strlen(argv[2])) == 0))
		{
			free(str);
			break ;
		}
		else
			write(temp_file, str, ft_strlen(str));
		free(str);
	}
	close(temp_file);
	files->input = open(".here_doc", O_RDONLY);
	files->output = open(argv[argc - 1], O_APPEND | O_CREAT | O_WRONLY, 0644);
}

int	main(int argc, char **argv, char **env)
{
	t_files	files;

	if (argc < 5)
		exit_error(ARG_NUM_ERROR);
	if (ft_strncmp("here_doc", argv[1], 8) == 0)
		open_heredoc(argv, argc, &files);
	else
	{
		files.input = open(argv[1], O_RDONLY);
		files.output = open(argv[argc - 1], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	}
	if (files.input < 0)
	{
		close(files.output);
		exit_error(OPEN_ERROR);
	}
	if (files.output < 0)
	{
		close(files.input);
		exit_error(OPEN_ERROR);
	}
	command_loop(argc, argv, env, &files);
	if (ft_strncmp("here_doc", argv[1], 8) == 0)
		unlink(".here_doc");
	return (0);
}
