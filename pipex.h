#ifndef PIPEX_h
#define PIPEX_h

#include <sys/types.h>
#include <sys/wait.h>

char	**ft_split(char *s, char c);
void	child_process(char **argv, char **env, int *p, int fd);
void	parent_process(char **argv, char **env, int *p, int fd);
char	*ft_get_path(char *cmd, char **env);
#endif
