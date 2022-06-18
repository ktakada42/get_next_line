/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakada <ktakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 00:24:18 by ktakada           #+#    #+#             */
/*   Updated: 2022/06/18 20:03:10 by ktakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	get_lf_index_from_buf(char	*buf);

char	*get_next_line(int fd)
{
	static char	*save;
	char		*buf;
	char		*line;
	ssize_t		cc;
	ssize_t		lf_index;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buf == NULL)
		return (NULL);
	cc = read(fd, buf, BUFFER_SIZE);
	if (cc == -1)
	{
		free (buf);
		return (NULL);
	}
	else
	{
		buf[cc] = '\0';
		lf_index = get_lf_index_from_buf(buf);
		if (lf_index >= 0)
		{
			line = ft_strjoin(save, buf);
			if (line == NULL)
			{
				free(buf);
				return (NULL);
			}
			save = buf + lf_index + 1;
			return (line);
		}
		else
		{
			save = ft_strjoin(save, buf);
			if (save == NULL)
			{
				free(buf);
				return (NULL);
			}
		}
	}
}

ssize_t	get_lf_index_from_buf(char	*buf)
{
	ssize_t	i;

	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*str;

	fd = open("hello.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	str = get_next_line(fd);
	printf("%s\n", str);
	return (0);
}
