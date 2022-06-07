/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakada <ktakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 00:24:18 by ktakada           #+#    #+#             */
/*   Updated: 2022/06/07 21:12:50 by ktakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*buf;
	ssize_t		cc;

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
		return (buf);
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
