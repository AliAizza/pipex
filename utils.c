/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaizza <aaizza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 01:24:52 by aaizza            #+#    #+#             */
/*   Updated: 2022/03/12 22:23:45 by aaizza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	compare_strings(char *s1, char *s2)
{
	int	len;

	if (ft_strlen(s1) > ft_strlen(s2))
		len = ft_strlen(s1);
	else
		len = ft_strlen(s2);
	if (!ft_strncmp(s1, s2, len))
		return (1);
	return (0);
}

void	get_commands(t_command *cmd, char **argv, char **env, int size)
{
	int	i;

	i = 0;
	if (compare_strings(argv[1], "here_doc"))
		argv += 3;
	else
		argv += 2;
	while (i < size)
	{
		pipe(cmd[i].p);
		cmd[i].args = ft_split(argv[i], ' ');
		cmd[i].path = ft_get_path(cmd[i].args[0], env);
		i++;
	}
}

int	open_file(char *path)
{
	int	fd;

	fd = open(path, O_RDWR);
	if (fd < 0)
	{
		perror("./pipex");
		exit(1);
	}
	return (fd);
}

void	read_form_stdout(char *limit, int fd)
{
	char	*line;

	line = get_next_line(1);
	while (ft_strncmp(limit, line, ft_strlen(line)))
	{
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(1);
	}
	free(line);
	free(limit);
}

void	handle_input(t_command *cmd, char *input)
{
	int	fd;

	if (compare_strings(input, "here_doc"))
	{
		fd = open_file("/tmp/.temp");
	}
	else
	{
		fd = open_file(input);
	}
	dup2(fd, 0);
	dup2(cmd[0].p[1], 1);
}
