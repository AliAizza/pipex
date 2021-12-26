#include <unistd.h>
#include <fcntl.h>
#include "pipex.h"
void	child_process(char **argv, char **env, int *p, int fd)
{
	char	*path;
	char	**cmd;

	cmd = ft_split(argv[2], ' ');
	path = ft_get_path(cmd[0], env);
	dup2(fd, 0);
	dup2(p[1], 1);
	close(p[0]);
	execve(path, cmd, env);
}

void	parent_process(char **argv, char **env, int *p, int fd)
{
	char	*path;
	char	**cmd;

	wait(0);
	cmd = ft_split(argv[3], ' ');
	path = ft_get_path(cmd[0], env);
	dup2(fd, 1);
	dup2(p[0], 0);
	close(p[1]);
	execve(path, cmd, env);
}
