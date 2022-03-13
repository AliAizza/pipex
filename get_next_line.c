/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaizza <aaizza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 01:21:19 by aaizza            #+#    #+#             */
/*   Updated: 2022/03/12 22:21:40 by aaizza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_till_line(char *s)
{
	int	i;

	i = 0;
	if (!s[0])
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	return (ft_substr(s, 0, i + 1));
}

char	*ft_get_remain(char *s)
{
	int		i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\n')
		{
			str = ft_substr(s, i + 1, ft_strlen(s));
			free(s);
			return (str);
		}
		i++;
	}
	free(s);
	return (0);
}

char	*ft_read_line(int fd, char *s)
{
	char	*str;
	int		i;

	str = malloc (2);
	if (!str)
	{
		free(s);
		return (NULL);
	}
	i = 1;
	while (!ft_checkline(s) && i)
	{
		i = read (fd, str, 1);
		if (i == -1)
		{
			free (str);
			return (NULL);
		}
		str[i] = '\0';
		s = ft_strjoin2(s, str);
	}
	free (str);
	return (s);
}

char	*get_next_line(int fd)
{
	char		*new;
	static char	*rem;

	if (fd < 0)
		return (NULL);
	rem = ft_read_line(fd, rem);
	if (!rem)
		return (NULL);
	new = ft_till_line(rem);
	rem = ft_get_remain(rem);
	return (new);
}
