/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 18:09:33 by mdos-san          #+#    #+#             */
/*   Updated: 2015/12/11 19:56:55 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "get_next_line.h"

static int	lengt_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n')
		i++;
	return (i + 1);
}

static int	realloc_str(char ***line, char **st_str, char **tmp, int *len)
{
	**line = ft_strdup(*st_str);
	if (*st_str)
		free(*st_str);
	*st_str = (char*)malloc(*len + 1);
	if (!*st_str)
		return (0);
	ft_bzero(*st_str, *len);
	ft_strcat(*st_str, **line);
	if (**line)
		free(**line);
	ft_strcat(*st_str, *tmp);
	ft_bzero(*tmp, BUFF_SIZE);
	return (1);
}

static void	truncate_str(char ***line, char **st_str, char **tmp)
{
	free(*tmp);
	*tmp = ft_strchr(*st_str, '\n');
	**tmp = 0;
	**line = ft_strdup(*st_str);
	**tmp = '\n';
	*tmp = ft_strdup(*st_str + lengt_line(*st_str));
	if (*st_str)
		free(*st_str);
	*st_str = *tmp;
}

int		get_next_line(int const fd, char **line)
{
	static char	*st_str = 0;
	char		*tmp;
	int			len;
	int			ret;

	len = ft_strlen(st_str);
	tmp = ft_strnew(BUFF_SIZE);
	while (!ft_strchr(st_str, '\n'))
	{
		ret = read(fd, tmp, BUFF_SIZE);
		if (ret == -1)
			return (-1);
		if (ret == 0)
		{
			*line = ft_strdup(st_str);
			if (ft_strlen(*line) > 0)
			{
				ft_strdel(&st_str);
				return (1);
			}
			return (0);
		}
		len += ret;
		if (!realloc_str(&line, &st_str, &tmp, &len))
			return (-1);
	}
	truncate_str(&line, &st_str, &tmp);
	return (1);
}
