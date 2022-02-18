/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaizza <aaizza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:13:59 by aaizza            #+#    #+#             */
/*   Updated: 2022/02/18 03:58:57 by aaizza           ###   ########.fr       */
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
