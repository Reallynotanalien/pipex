/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:57:01 by kafortin          #+#    #+#             */
/*   Updated: 2023/01/23 17:52:17 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./Libft/libft.h"
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>

typedef struct path
{
	char	*path;
	char	*part;
	char	**paths;
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
	pid_t	pid1;
	pid_t	pid2;
}			t_files;

void	free_tab(char **tab);
void	free_struct(t_cmd *cmd);
void	exit_error(char *error);
void	open_files(t_files *files, char **argv);
void	close_all(t_files *files);

#endif