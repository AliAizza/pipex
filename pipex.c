/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaizza <aaizza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 22:32:34 by aaizza            #+#    #+#             */
/*   Updated: 2022/02/23 22:40:41 by aaizza           ###   ########.fr       */
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

void	dup_all(t_command *cmd, char **argv, int i, int size)
{
	int	fd;
	int	k;

	k = 2;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		k = 3;
	if (i == 0)
		handle_input(cmd, argv[1]);
	else if (i == size - 1)
	{
		if (!compare_strings(argv[1], "here_doc"))
			fd = open(argv[size + k], O_CREAT | O_RDWR | O_TRUNC, 0664);
		else
			fd = open(argv[size + k], O_RDWR | O_CREAT | O_APPEND, 0664);
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

int	ft_norm(char **argv, int argc)
{
	int	size;
	int	fd;

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

int	main(int argc, char **argv, char **env)
{
	int			size;
	t_command	*cmd;
	int			i;

	size = ft_norm(argv, argc);
	cmd = malloc((size) * sizeof(t_command));
	get_commands(cmd, argv, env, size);
	i = 0;
	while (i < size)
	{
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			close_unused_pipes(cmd, i, size);
			dup_all(cmd, argv, i, size);
			check_path(cmd, i);
			while(1);
			if (execve(cmd[i].path, cmd[i].args, env) == -1)
				perror("./pipex");	
			exit(1);
		}
		i++;
	}
	close_all_pipes(cmd, size);
	wait_all_child_processors(cmd, size);
}
