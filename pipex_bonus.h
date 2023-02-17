/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:57:01 by kafortin          #+#    #+#             */
/*   Updated: 2023/02/16 19:06:57 by kafortin         ###   ########.fr       */
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
t_cmd	*find_cmd(char *argv, char **env);

#endif