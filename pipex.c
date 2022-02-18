/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaizza <aaizza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 22:32:34 by aaizza            #+#    #+#             */
/*   Updated: 2022/02/18 03:56:00 by aaizza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	dup_all(t_command *cmd, char **argv, int i, int size)
{
	int	fd;
	int	k;

	k = 2;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		k = 3;
	if (i == 0)
		handle_input(cmd, argv[1], argv[2]);
	else if (i == size - 1)
	{
		fd = open(argv[size + k], O_RDWR | O_CREAT, 0777);
		if (fd < 0)
		{
			perror("Error: ");
			exit(1);
		}
		dup2(cmd[i - 1].p[0], 0);
		dup2(fd, 1);
	}
	else
	{
		dup2(cmd[i - 1].p[0], 0);
		dup2(cmd[i].p[1], 1);
	}
}

void	close_unused_pipes(t_command *cmd, int process_index, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (i != process_index - 1)
			close(cmd[i].p[0]);
		if (i != process_index)
			close(cmd[i].p[1]);
		i++;
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

int	ft_norm(char **argv, int argc, int size, int fd)
{
	if (compare_strings(argv[1], "here_doc"))
	{
		fd = open("/tmp/.temp", O_RDWR | O_CREAT | O_TRUNC, 0777);
		read_form_stdout(ft_strjoin(argv[2], "\n"), fd);
		close(fd);
		size = argc - 4;
	}
	else
		size = argc - 3;
	return (size);
}

int	main(int argc, char **argv, char **env)
{
	int			size;
	t_command	*cmd;
	t_data		data;
	char		*str;
	int			fd;

	size = ft_norm(argv, argc, size, fd);
	cmd = malloc((size) * sizeof(t_command));
	get_commands(cmd, argv, env, size);
	fd = 0;
	while (fd < size)
	{
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			close_unused_pipes(cmd, fd, size);
			dup_all(cmd, argv, fd, size);
			if (execve(cmd[fd].path, cmd[fd].args, env) == -1)
				exit(1);
		}
		fd++;
	}
}
