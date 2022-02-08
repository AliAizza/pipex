/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaizza <aaizza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 00:55:46 by aaizza            #+#    #+#             */
/*   Updated: 2022/02/07 15:42:11 by aaizza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_issep(char i, char c)
{
	if (i == c)
		return (1);
	return (0);
}

static int	ft_count(char *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (!ft_issep(s[0], c))
		count++;
	while (s[i])
	{
		if (ft_issep(s[i], c)
			&& !ft_issep(s[i + 1], c) && s[i + 1])
			count++;
		i++;
	}
	return (count);
}

static int	ft_wordlen(char *s, char c)
{
	int	i;

	i = 0;
	while (!ft_issep(s[i], c) && s[i])
		i++;
	return (i);
}

static char	*ft_put(char *s, char sep)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = ft_wordlen(s, sep);
	str = malloc((j + 1) * sizeof(char));
	if (!s)
		return (NULL);
	while (s[i] && j > 0)
	{
		str[i] = (char)s[i];
		i++;
		j--;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char *s, char c)
{
	char		**new;
	int			i;
	int			j;

	if (!s)
		return (NULL);
	new = malloc(sizeof(char *) * ((ft_count(s, c)) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (ft_issep(s[i], c) && s[i])
			i++;
		if (!ft_issep(s[i], c) && s[i])
		{
			new[j++] = ft_put(s + i, c);
			i += ft_wordlen(s + i, c);
		}
	}
	new[j] = NULL;
	return (new);
}
