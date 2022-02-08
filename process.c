/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaizza <aaizza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:13:59 by aaizza            #+#    #+#             */
/*   Updated: 2022/02/07 22:28:19 by aaizza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

void	child_process(char **argv, char **env, int *p, int fd)
{
	char	*path;
	char	**cmd;

	if (fd == -1)
	{
		ft_putstr("./pipex: No such file or directory: ");
		ft_putstr(argv[1]);
		ft_putstr("\n");
		return ;
	}
	cmd = ft_split(argv[2], ' ');
	path = ft_get_path(cmd[0], env);
	if (access(path, F_OK) != 0)
	{
		ft_putstr("./pipex: command not found: ");
		ft_putstr(cmd[0]);
		ft_putstr("\n");
	}
	dup2(fd, 0);
	dup2(p[1], 1);
	close(p[1]);
	close(p[0]);
	execve(path, cmd, env);
}

void	parent_process(char **argv, char **env, int *p, int fd)
{
	char	*path;
	char	**cmd;

	wait(NULL);
	cmd = ft_split(argv[3], ' ');
	path = ft_get_path(cmd[0], env);
	if (access(path, F_OK) != 0)
	{
		ft_putstr("./pipex: command not found: ");
		ft_putstr(cmd[0]);
		ft_putstr("\n");
	}
	dup2(fd, 1);
	dup2(p[0], 0);
	close(p[0]);
	close(p[1]);
	execve(path, cmd, env);
}
