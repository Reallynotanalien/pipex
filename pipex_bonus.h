/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:57:01 by kafortin          #+#    #+#             */
/*   Updated: 2023/03/14 17:48:05 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "./Libft/libft.h"
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>

# define FORK_ERROR "Error: fork did not work."
# define PIPE_ERROR "Error: pipe did not work."
# define ARG_NUM_ERROR "Error: invalid number of arguments."
# define PATH_ERROR "Error: path not found."
# define COMMAND_ERROR "Error: command not found."
# define ENV_ERROR "Error: PATH is not an environment variable."
# define OPEN_ERROR "Error: file could not be opened."

typedef struct path
{
	char	*path;
	char	*join;
	char	**env;
}				t_path;

typedef struct cmd
{
	t_path	path;
	char	**cmd;
}				t_cmd;

typedef struct files
{
	int		fd[2];
	int		input;
	int		output;
	pid_t	pid;
}			t_files;

void	open_errors(t_files *files);
void	free_struct(t_cmd *cmd);
void	exit_error(char *error);
void	close_all(t_files *files);
t_cmd	*find_cmd(char *argv, char **env, t_files *files);
void	close_exit(char *error, t_files *files);

#endif