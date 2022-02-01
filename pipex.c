/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaizza <aaizza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 22:32:34 by aaizza            #+#    #+#             */
/*   Updated: 2022/02/01 12:02:35 by aaizza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	int	p[2];
	int	pid;
	int	fd1;
	int	fd2;

	pipe(p);
	pid = fork();
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	system("leaks pipex");
	if (pid == 0)
		child_process(argv, env, p, fd1);
	else
		parent_process(argv, env, p, fd2);
}
