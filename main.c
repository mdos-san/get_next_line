#include "get_next_line.h"
#include "libft.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int	main(void)
{
	int		fd;
	int		i;
	char	*line;

	line = 0;
	i = 0;
	while (i < 10)
	{
		fd = open("test", O_RDONLY);
		while (get_next_line(fd, &line))
			ft_putendl(line);
		if (line)
			free(line);
		line = 0;
		close(fd);
		i++;
	}
	return (0);
}
