/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaizza <aaizza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:39:41 by aaizza            #+#    #+#             */
/*   Updated: 2022/02/28 22:39:45 by aaizza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*new;

	new = (char *)str;
	i = 0;
	while (new[i])
	{
		if (new[i] == ((char)c))
			return (&new[i]);
		i++;
	}
	if (new[i] == (char)c)
		return (&new[i]);
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	check_path(t_command *cmd, int i)
{
	if (!cmd[i].path)
	{
		if (ft_strchr(cmd[i].args[0], '/'))
			cmd[i].path = cmd[i].args[0];
		else
		{
			ft_putstr_fd("./pipex: command not found\n", 2);
			exit(1);
		}
	}
}

void	wait_all_child_processors(t_command *cmd, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		waitpid(cmd[i].pid, 0, 0);
		i++;
	}
}

void	close_all_pipes(t_command *cmd, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		close(cmd[i].p[0]);
		close(cmd[i].p[1]);
		i++;
	}
}
