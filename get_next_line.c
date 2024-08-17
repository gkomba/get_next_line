/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <<marvin@42.fr> >                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:29:49 by gkomba            #+#    #+#             */
/*   Updated: 2024/08/17 09:14:25 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	chr[BUFFER_SIZE];
	char		str[7000000];
	static int	buffer_readed;
	static int	buffer_pos;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (buffer_pos >= buffer_readed)
			if (read_buffer(fd, chr, &buffer_readed, &buffer_pos) <= 0)
				break ;
		str[i++] = chr[buffer_pos++];
		if (str[i - 1] == '\n')
			break ;
	}
	str[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_string_dup(str));
}

int main(int ac, char **av)
{
	int fd;
	char *line;

	fd = open(av[1], O_RDONLY);
	while (line = get_next_line(fd))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
}