/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaizza <aaizza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:16:46 by aaizza            #+#    #+#             */
/*   Updated: 2022/02/18 03:58:51 by aaizza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_command
{
	char	*path;
	char	**args;
	int		pid;
	int		p[2];
}	t_command;

typedef struct s_data {
	char	**arr;
	char	*input;
	char	*output;
	char	*limit;
	int		p[2];
	int		size;
}	t_data;

char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
int		ft_strlen(char *str);
int		ft_strncmp(char *s1, char *s2, int n);
void	child_process(char **argv, char **env, int *p, int fd);
void	parent_process(char **argv, char **env, int *p, int fd);
char	*ft_get_path(char *command, char **env);
void	ft_putstr(char *s);
int		compare_strings(char *s1, char *s2);
void	get_commands(t_command *cmd, char **argv, char **env, int size);
int		open_file(char *path);
void	read_form_stdout(char *limit, int fd);
void	handle_input(t_command *cmd, char *input, char *limit);
char	*ft_substr(char *s, int start, int len);
int		ft_checkline(char *s);

#endif
