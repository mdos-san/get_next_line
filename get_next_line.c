/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 18:09:33 by mdos-san          #+#    #+#             */
/*   Updated: 2015/12/11 17:07:01 by mdos-san         ###   ########.fr       */
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

int		get_next_line(int const fd, char **line)
{
	static char	*st_str = 0;
	char		*tmp;
	int			len;
	int			ret;

	len = ft_strlen(st_str);
	tmp = (char*)malloc(BUFF_SIZE + 1);
	if (!tmp)
		return (-1);
	tmp[BUFF_SIZE] = 0;
	ft_bzero(tmp, BUFF_SIZE);
	while (!ft_strchr(st_str, '\n'))
	{
		ret = read(fd, tmp, BUFF_SIZE);
		if (ret == -1)
			return (-1);
		if (ret == 0)
		{
			*line = ft_strdup(st_str);
			return (0);
		}
		len += ret;
		*line = ft_strdup(st_str);
		if (st_str)
			free(st_str);
		st_str = (char*)malloc(len +1);
		if (!st_str)
			return (-1);
		ft_bzero(st_str, len);
		ft_strcat(st_str, *line);
		if (*line)
			free(*line);
		ft_strcat(st_str, tmp);
		ft_bzero(tmp, BUFF_SIZE);
	}
	free(tmp);
	tmp = ft_strchr(st_str, '\n');
	*tmp = 0;
	*line = ft_strdup(st_str);
	*tmp = '\n';
	tmp = ft_strdup(st_str + lengt_line(st_str));
	if (st_str)
		free(st_str);
	st_str = tmp;
	return (1);
}
