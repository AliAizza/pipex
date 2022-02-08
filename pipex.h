/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaizza <aaizza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:16:46 by aaizza            #+#    #+#             */
/*   Updated: 2022/02/07 17:39:52 by aaizza           ###   ########.fr       */
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

char	**ft_split(char *s, char c);
void	child_process(char **argv, char **env, int *p, int fd);
void	parent_process(char **argv, char **env, int *p, int fd);
char	*ft_get_path(char *cmd, char **env);
#endif
