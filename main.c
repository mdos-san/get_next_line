/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 16:01:57 by mdos-san          #+#    #+#             */
/*   Updated: 2015/12/11 18:29:25 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"

int	main(int ac, char **av)
{
	int		fd;
	char	*line;

	if (ac > 2)
		return (0);
	line = 0;
	if (ac == 2)
		fd = open(av[1], O_RDONLY);
	if (ac == 1)
		fd = 0;
	while (get_next_line(fd, &line) > 0)
		ft_putendl(line);
	return (0);
}
